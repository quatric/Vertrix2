"""Compare surface addressing and pixel access with the original x86 routines."""
import argparse
import ctypes
import json
import random
import subprocess
from pathlib import Path
from original import Original, BOARD, BLOCKS
import struct

class Surface(ctypes.Structure):
    _fields_ = [("data",ctypes.POINTER(ctypes.c_uint8)),("size",ctypes.c_size_t),
                ("width",ctypes.c_uint32),("height",ctypes.c_uint32),
                ("stride",ctypes.c_uint32),("bytes_per_pixel",ctypes.c_uint8)]

class Clip(ctypes.Structure):
    _fields_=[(name,ctypes.c_int16) for name in ("left","right","top","bottom")]

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("executable",type=Path)
    parser.add_argument("--build-dir",type=Path,required=True)
    args=parser.parse_args()
    args.build_dir.mkdir(parents=True,exist_ok=True)
    root=Path(__file__).resolve().parents[1]
    library=args.build_dir.resolve()/"surface.dylib"
    subprocess.run(["cc","-shared","-fPIC","-O2","-Wall","-Wextra","-Werror",
                    str(root/"source/surface.c"),str(root/"source/render_geometry.c"),str(root/"source/render_dispatch.c"),"-o",str(library)],check=True)
    native=ctypes.CDLL(str(library))
    native.vertrix_surface_offset.argtypes=[ctypes.c_uint32,ctypes.c_uint8,ctypes.c_int32,ctypes.c_int32]
    native.vertrix_surface_offset.restype=ctypes.c_uint32
    native.vertrix_surface_read.argtypes=[ctypes.POINTER(Surface),ctypes.c_uint32,ctypes.c_uint32,ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_surface_write.argtypes=[ctypes.POINTER(Surface),ctypes.c_uint32,ctypes.c_uint32,ctypes.c_uint32]
    native.vertrix_render_direct_pixel.argtypes=[ctypes.c_uint32,ctypes.c_uint8]
    native.vertrix_render_direct_pixel.restype=ctypes.c_uint32
    native.vertrix_render_direct_write.argtypes=[ctypes.POINTER(Surface),ctypes.c_uint8,ctypes.c_uint32,ctypes.c_uint32,ctypes.c_uint32]
    native.vertrix_render_effect_pixel.argtypes=[ctypes.c_uint32,ctypes.c_uint32,ctypes.c_uint8,ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_surface_copy32.argtypes=[ctypes.POINTER(Surface),ctypes.c_uint32,ctypes.c_uint32,
        ctypes.POINTER(Surface),ctypes.c_uint32,ctypes.c_uint32,ctypes.c_uint16,ctypes.c_uint16]
    native.vertrix_surface_alpha32.argtypes=native.vertrix_surface_copy32.argtypes
    native.vertrix_sprite_draw32.argtypes=[ctypes.POINTER(Surface),ctypes.POINTER(Surface),
        ctypes.c_int16,ctypes.c_int16,ctypes.c_uint8,Clip,Clip,ctypes.c_int]
    native.vertrix_surface_binary32.argtypes=native.vertrix_surface_copy32.argtypes
    native.vertrix_surface_sample_row32.argtypes=[ctypes.POINTER(Surface),ctypes.c_uint32,ctypes.c_uint32,
        ctypes.POINTER(Surface),ctypes.c_uint32,ctypes.c_uint32,ctypes.POINTER(ctypes.c_uint8),ctypes.c_size_t,ctypes.c_uint16]
    native.vertrix_surface_sample32.argtypes=[ctypes.POINTER(Surface),ctypes.c_uint32,ctypes.c_uint32,
        ctypes.POINTER(Surface),ctypes.c_uint32,ctypes.c_uint32,ctypes.POINTER(ctypes.c_uint8),ctypes.c_size_t,
        ctypes.POINTER(ctypes.c_uint8),ctypes.c_size_t,ctypes.c_uint16,ctypes.c_uint16]
    native.vertrix_render_scale_advances.argtypes=[ctypes.c_uint8,ctypes.c_uint32,ctypes.c_uint32,ctypes.POINTER(ctypes.c_uint8)]
    native.vertrix_sprite_draw_scaled32.argtypes=[ctypes.POINTER(Surface),ctypes.POINTER(Surface),
        ctypes.c_int16,ctypes.c_int16,ctypes.c_uint8,ctypes.c_uint8,Clip,Clip]
    native.vertrix_surface_sample_binary_row32.argtypes=native.vertrix_surface_sample_row32.argtypes
    native.vertrix_surface_sample_binary32.argtypes=native.vertrix_surface_sample32.argtypes
    native.vertrix_sprite_draw_scaled_binary32.argtypes=native.vertrix_sprite_draw_scaled32.argtypes
    native.vertrix_surface_sample_effect32.argtypes=native.vertrix_surface_sample32.argtypes+[ctypes.c_uint8,ctypes.c_int]
    native.vertrix_sprite_draw_scaled_effect32.argtypes=native.vertrix_sprite_draw_scaled32.argtypes+[ctypes.c_uint8,ctypes.c_int]
    native.vertrix_render_weighted_pixel.argtypes=[ctypes.c_uint32,ctypes.c_uint32,ctypes.c_uint8,ctypes.POINTER(ctypes.c_uint32)]
    native.vertrix_surface_sample_weighted32.argtypes=native.vertrix_surface_sample_effect32.argtypes
    native.vertrix_sprite_draw_scaled_weighted32.argtypes=native.vertrix_sprite_draw_scaled_effect32.argtypes
    oracle=Original(args.executable)
    oracle.call(0x480739,stop=0x480792)
    assert bytes(oracle.cpu.mem_read(0x558CF0,101*256))==bytes(channel*amount//100
        for amount in range(101) for channel in range(256))
    oracle.call(0x4B9050)
    for mode in range(1,16):
        output=(ctypes.c_uint8*1024)()
        assert native.vertrix_render_scale_advances(mode,0,1024,output)
        assert bytes(output)==bytes(oracle.cpu.mem_read(0x5C1C00+mode*1024,1024))
    unchanged=(ctypes.c_uint8*2)(123,45)
    for mode,start,count in ((0,0,2),(16,0,2),(1,1023,2),(1,0,1025)):
        assert not native.vertrix_render_scale_advances(mode,start,count,unchanged)
        assert bytes(unchanged)==bytes((123,45))
    oracle.call(0x4807EA,stop=0x48087A)
    table=bytes(oracle.cpu.mem_read(0x588600,65536))
    assert table==bytes(channel*(255-alpha)//255 for alpha in range(256) for channel in range(256))
    rng=random.Random(0x478EB0)
    for _ in range(10000):
        stride=rng.randrange(2**32)
        bpp=rng.randrange(256)
        x,y=rng.randrange(-2**31,2**31),rng.randrange(-2**31,2**31)
        descriptor=bytearray(32)
        struct.pack_into("<I",descriptor,0,0)
        descriptor[12]=bpp
        struct.pack_into("<I",descriptor,20,stride)
        oracle.cpu.mem_write(BOARD,bytes(descriptor))
        expected=oracle.call(0x478EB0,edx=x&0xffffffff,ebx=y&0xffffffff)
        assert native.vertrix_surface_offset(stride,bpp,x,y)==expected
    for index in range(6000):
        bpp=(1,2,4)[index%3]
        width,height=rng.randrange(1,33),rng.randrange(1,33)
        stride=width*bpp+rng.randrange(8)
        data=rng.randbytes(stride*height)
        x,y=rng.randrange(width),rng.randrange(height)
        value=rng.randrange(2**32)
        expected_offset,expected_read,expected_data=oracle.surface_pixel(data,width,height,stride,bpp,x,y,value)
        storage=(ctypes.c_uint8*len(data)).from_buffer_copy(data)
        surface=Surface(storage,len(data),width,height,stride,bpp)
        result=ctypes.c_uint32()
        assert native.vertrix_surface_offset(stride,bpp,x,y)==expected_offset
        assert native.vertrix_surface_read(ctypes.byref(surface),x,y,ctypes.byref(result))
        assert result.value==expected_read
        assert native.vertrix_surface_write(ctypes.byref(surface),x,y,value)
        assert bytes(storage)==expected_data
        result.value=123
        assert not native.vertrix_surface_read(ctypes.byref(surface),width,y,ctypes.byref(result))
        assert result.value==123
        assert not native.vertrix_surface_write(ctypes.byref(surface),x,height,value)
        assert bytes(storage)==expected_data
    direct_cases=30000
    for index in range(direct_cases):
        source=rng.randrange(2**32)
        format_byte=(4,2,1,0,3,255)[index%6]
        address={4:0x48D720,2:0x49B4A0,1:0x4933E0,0:0x4A3540}.get(format_byte,0x48D720)
        bpp={0:1,1:2,2:2}.get(format_byte,4)
        oracle.cpu.mem_write(BLOCKS,struct.pack("<I",source))
        oracle.cpu.mem_write(BLOCKS+16,bytes([0xA5])*16)
        for global_address in (0x5BB764,):
            oracle.cpu.mem_write(global_address,struct.pack("<I",BLOCKS))
        for global_address in (0x5BB768,0x5BB780,0x5BB778):
            oracle.cpu.mem_write(global_address,struct.pack("<I",BLOCKS+19))
        oracle.call(address)
        expected=bytes(oracle.cpu.mem_read(BLOCKS+16,16))
        value=int.from_bytes(expected[3:3+bpp],"little")
        assert native.vertrix_render_direct_pixel(source,format_byte)==value
        storage=(ctypes.c_uint8*16)(*([0xA5]*16))
        surface=Surface(storage,16,1,1,bpp,bpp)
        surface.data=ctypes.cast(ctypes.byref(storage,3),ctypes.POINTER(ctypes.c_uint8))
        surface.size=13
        assert native.vertrix_render_direct_write(ctypes.byref(surface),format_byte,0,0,source)
        assert bytes(storage)==expected
    effect_cases=35000
    addresses={1:0x48DB70,3:0x48DCD0,4:0x48DD00,5:0x48DD50,6:0x48DDA0,7:0x48DDF0,8:0x48DE10}
    for index in range(effect_cases):
        effect=tuple(addresses)[index%7]
        source,destination=rng.randrange(2**32),rng.randrange(2**32)
        oracle.cpu.mem_write(BLOCKS,struct.pack("<I",source))
        oracle.cpu.mem_write(BLOCKS+16,struct.pack("<I",destination))
        oracle.cpu.mem_write(0x5BB764,struct.pack("<I",BLOCKS))
        oracle.cpu.mem_write(0x5BB768,struct.pack("<I",BLOCKS+16))
        oracle.call(addresses[effect])
        expected=struct.unpack("<I",oracle.cpu.mem_read(BLOCKS+16,4))[0]
        result=ctypes.c_uint32(123)
        assert native.vertrix_render_effect_pixel(source,destination,effect,ctypes.byref(result))
        assert result.value==expected,(effect,source,destination,result.value,expected)
    for effect in (0,2,9,10,255):
        result=ctypes.c_uint32(123)
        assert not native.vertrix_render_effect_pixel(0,0,effect,ctypes.byref(result))
        assert result.value==123
    copy_cases=2000
    for index in range(copy_cases*3):
        width,height=rng.randrange(1,24),rng.randrange(1,24)
        source_stride=(width+rng.randrange(8))*4
        target_stride=width*4+rng.randrange(16)
        source_data=rng.randbytes(source_stride*height)
        target_data=rng.randbytes(target_stride*height)
        oracle.cpu.mem_write(BLOCKS,source_data)
        oracle.cpu.mem_write(BLOCKS+8192,target_data)
        for address,value in [(0x5BB764,BLOCKS),(0x5BB768,BLOCKS+8192),
                              (0x5BB79C,source_stride//4-width),(0x5BB7C8,target_stride-width*4)]:
            oracle.cpu.mem_write(address,struct.pack("<I",value))
        oracle.cpu.mem_write(0x5BB750,struct.pack("<HH",width,height))
        oracle.call((0x4AB310,0x4AB380,0x4AB2A0)[index//copy_cases])
        expected=bytes(oracle.cpu.mem_read(BLOCKS+8192,len(target_data)))
        src=(ctypes.c_uint8*len(source_data)).from_buffer_copy(source_data)
        dst=(ctypes.c_uint8*len(target_data)).from_buffer_copy(target_data)
        source=Surface(src,len(src),width,height,source_stride,4)
        target=Surface(dst,len(dst),width,height,target_stride,4)
        operation=(native.vertrix_surface_copy32,native.vertrix_surface_alpha32,native.vertrix_surface_binary32)[index//copy_cases]
        assert operation(ctypes.byref(source),0,0,ctypes.byref(target),0,0,width,height)
        assert bytes(dst)==expected
        assert bytes(src)==source_data
    draw_cases=1000
    for index in range(draw_cases):
        width,height=rng.randrange(1,25),rng.randrange(1,25)
        px,py=rng.randrange(-25,80),rng.randrange(-25,80)
        mode=rng.choice((0,1,3,4))
        custom=(10,50,10,50)
        source_data=rng.randbytes(width*height*4)
        target_data=rng.randbytes(64*64*4)
        clipped=oracle.sprite_clip(px,py,width,height,custom,mode,(64,64),custom)
        oracle.cpu.mem_write(BLOCKS,source_data)
        oracle.cpu.mem_write(BLOCKS+8192,target_data)
        if clipped is not None:
            left,right,top,bottom,cw,ch,offset,flag=clipped
            for address,value in [(0x5BB764,BLOCKS+offset*4),
                    (0x5BB768,BLOCKS+8192+(top*64+left)*4),
                    (0x5BB79C,width-cw),(0x5BB7C8,(64-cw)*4)]:
                oracle.cpu.mem_write(address,struct.pack("<I",value))
            oracle.cpu.mem_write(0x5BB750,struct.pack("<HH",cw,ch))
            oracle.draw_prepared_dispatch(BLOCKS,16,index%3 == 2,alpha=index%3 == 1)
        expected=bytes(oracle.cpu.mem_read(BLOCKS+8192,len(target_data)))
        src=(ctypes.c_uint8*len(source_data)).from_buffer_copy(source_data)
        dst=(ctypes.c_uint8*len(target_data)).from_buffer_copy(target_data)
        source=Surface(src,len(src),width,height,width*4,4)
        target=Surface(dst,len(dst),64,64,256,4)
        valid=native.vertrix_sprite_draw32(ctypes.byref(source),ctypes.byref(target),px,py,mode,
                                        Clip(*custom),Clip(*custom),index%3)
        assert valid==int(clipped is not None),(px,py,width,height,clipped,valid)
        assert bytes(dst)==expected
    sampled_rows=2000
    for row_index in range(sampled_rows):
        width=rng.randrange(1,65)
        advances=bytes(rng.randrange(6) for _ in range(width))
        if row_index % 2:
            mode=rng.randrange(1,16)
            start=rng.randrange(64)
            table_steps=(ctypes.c_uint8*width)()
            assert native.vertrix_render_scale_advances(mode,start,width,table_steps)
            advances=bytes(table_steps)
        source_width=sum(advances)+1
        source_data=rng.randbytes(source_width*4)
        target_data=rng.randbytes(width*4)
        oracle.cpu.mem_write(BLOCKS,source_data)
        oracle.cpu.mem_write(BLOCKS+8192,target_data)
        oracle.cpu.mem_write(BLOCKS+16384,advances)
        for address,value in ((0x5BB764,BLOCKS),(0x5BB768,BLOCKS+8192),
                              (0x5BB7DC,BLOCKS+16384),(0x5BB72C,0x48D720)):
            oracle.cpu.mem_write(address,struct.pack("<I",value))
        oracle.cpu.mem_write(0x5BC016,struct.pack("<H",width))
        oracle.call(0x492550 if row_index%2 else 0x492710)
        expected=bytes(oracle.cpu.mem_read(BLOCKS+8192,len(target_data)))
        src=(ctypes.c_uint8*len(source_data)).from_buffer_copy(source_data)
        dst=(ctypes.c_uint8*len(target_data)).from_buffer_copy(target_data)
        steps=(ctypes.c_uint8*width).from_buffer_copy(advances)
        source=Surface(src,len(src),source_width,1,source_width*4,4)
        target=Surface(dst,len(dst),width,1,width*4,4)
        operation=native.vertrix_surface_sample_binary_row32 if row_index%2 else native.vertrix_surface_sample_row32
        assert operation(ctypes.byref(source),0,0,ctypes.byref(target),0,0,
                                                  steps,width,width)
        assert bytes(dst)==expected
    sampled_rectangles=4000
    for rectangle_index in range(sampled_rectangles):
        width,height=rng.randrange(1,9),rng.randrange(1,9)
        effects={1:0x48DB70,3:0x48DCD0,4:0x48DD00,5:0x48DD50,6:0x48DDA0,7:0x48DDF0,8:0x48DE10}
        effect=rng.choice(tuple(effects)) if rectangle_index>=1000 else 0
        binary=bool(rectangle_index%2)
        weighted=rectangle_index>=3000
        amount=rng.randrange(101)
        horizontal=bytes(rng.randrange(6) for _ in range(width))
        vertical=bytes(rng.randrange(6) for _ in range(height))
        sw,sh=sum(horizontal)+1,sum(vertical)+1
        source_data=rng.randbytes(sw*sh*4)
        stride=width*4+rng.randrange(8)
        target_data=rng.randbytes(stride*height)
        oracle.cpu.mem_write(BLOCKS,source_data)
        oracle.cpu.mem_write(BLOCKS+8192,target_data)
        oracle.cpu.mem_write(BLOCKS+16384,vertical)
        oracle.cpu.mem_write(BLOCKS+16640,horizontal)
        for address,value in ((0x5BB764,BLOCKS),(0x5BB76C,BLOCKS),
                (0x5BB768,BLOCKS+8192),(0x5BB770,BLOCKS+8192),
                (0x5BB7D4,BLOCKS+16384),(0x5BB7D8,BLOCKS+16640),
                (0x5BB7C0,sw),(0x5BB7C4,stride),(0x5BB72C,effects[effect] if effect else 0x48D720)):
            oracle.cpu.mem_write(address,struct.pack("<I",value))
        oracle.cpu.mem_write(0x5BB750,struct.pack("<HH",width,height))
        if weighted:
            for address,value in ((0x5BB72C,0x4902A0),(0x55F1F0,0x558CF0+amount*256),
                                  (0x55F1F4,0x558CF0+(100-amount)*256)):
                oracle.cpu.mem_write(address,struct.pack("<I",value))
        oracle.call(0x4928F0,eax=0x492550 if rectangle_index%2 else 0x492710)
        expected=bytes(oracle.cpu.mem_read(BLOCKS+8192,len(target_data)))
        src=(ctypes.c_uint8*len(source_data)).from_buffer_copy(source_data)
        dst=(ctypes.c_uint8*len(target_data)).from_buffer_copy(target_data)
        hs=(ctypes.c_uint8*width).from_buffer_copy(horizontal)
        vs=(ctypes.c_uint8*height).from_buffer_copy(vertical)
        source=Surface(src,len(src),sw,sh,sw*4,4)
        target=Surface(dst,len(dst),width,height,stride,4)
        operation=native.vertrix_surface_sample_binary32 if rectangle_index%2 else native.vertrix_surface_sample32
        if weighted:
            assert native.vertrix_surface_sample_weighted32(ctypes.byref(source),0,0,ctypes.byref(target),0,0,
                                                           hs,width,vs,height,width,height,amount,binary)
        elif effect:
            assert native.vertrix_surface_sample_effect32(ctypes.byref(source),0,0,ctypes.byref(target),0,0,
                                                         hs,width,vs,height,width,height,effect,binary)
        else:
            assert operation(ctypes.byref(source),0,0,ctypes.byref(target),0,0,
                             hs,width,vs,height,width,height)
        assert bytes(dst)==expected
    scaled_draws=6000
    for scaled_index in range(scaled_draws):
        sw,sh=rng.randrange(1,33),rng.randrange(1,33)
        mode=rng.randrange(1,16)
        effects={1:0x48DB70,3:0x48DCD0,4:0x48DD00,5:0x48DD50,6:0x48DDA0,7:0x48DDF0,8:0x48DE10}
        effect=rng.choice(tuple(effects)) if scaled_index>=2000 else 0
        weighted=scaled_index>=4000
        amount=rng.randrange(101)
        px,py=rng.randrange(-15,70),rng.randrange(-15,70)
        clip_mode=rng.choice((0,1,3,4))
        custom=(10,50,10,50)
        w,h=oracle.resource_measure(sw,sh,mode)
        clipped=oracle.sprite_clip(px,py,w,h,custom,clip_mode,(64,64),custom) if w and h else None
        offset=0
        if clipped is not None:
            left,right,top,bottom,cw,ch,_,_=clipped
            offset=oracle.scale_clip_offset(mode,sw,left-px,top-py,0)
        source_data=rng.randbytes(sw*sh*4)
        target_data=rng.randbytes(64*64*4)
        oracle.cpu.mem_write(BLOCKS,source_data)
        oracle.cpu.mem_write(BLOCKS+8192,target_data)
        if clipped is not None:
            for address,value in ((0x5BB764,BLOCKS+offset*4),(0x5BB76C,BLOCKS+offset*4),
                    (0x5BB768,BLOCKS+8192+(top*64+left)*4),(0x5BB770,BLOCKS+8192+(top*64+left)*4),
                    (0x5BB7D4,0x5C1C00+mode*1024+top-py),(0x5BB7D8,0x5C1C00+mode*1024+left-px),
                    (0x5BB7C0,sw),(0x5BB7C4,256),(0x5BB72C,effects[effect] if effect else 0x48D720)):
                oracle.cpu.mem_write(address,struct.pack("<I",value))
            oracle.cpu.mem_write(0x5BB750,struct.pack("<HH",cw,ch))
            if weighted:
                for address,value in ((0x5BB72C,0x4902A0),(0x55F1F0,0x558CF0+amount*256),
                                      (0x55F1F4,0x558CF0+(100-amount)*256)):
                    oracle.cpu.mem_write(address,struct.pack("<I",value))
            oracle.draw_prepared_dispatch(BLOCKS,mode,scaled_index%2,
                                         1 if weighted else effect,amount if weighted else 50,
                                         alpha=bool(scaled_index%4 < 2))
        expected=bytes(oracle.cpu.mem_read(BLOCKS+8192,len(target_data)))
        src=(ctypes.c_uint8*len(source_data)).from_buffer_copy(source_data)
        dst=(ctypes.c_uint8*len(target_data)).from_buffer_copy(target_data)
        source=Surface(src,len(src),sw,sh,sw*4,4)
        target=Surface(dst,len(dst),64,64,256,4)
        operation=native.vertrix_sprite_draw_scaled_binary32 if scaled_index%2 else native.vertrix_sprite_draw_scaled32
        if weighted:
            valid=native.vertrix_sprite_draw_scaled_weighted32(ctypes.byref(source),ctypes.byref(target),px,py,mode,
                clip_mode,Clip(*custom),Clip(*custom),amount,scaled_index%2)
        elif effect:
            valid=native.vertrix_sprite_draw_scaled_effect32(ctypes.byref(source),ctypes.byref(target),px,py,mode,
                clip_mode,Clip(*custom),Clip(*custom),effect,scaled_index%2)
        else:
            valid=operation(ctypes.byref(source),ctypes.byref(target),px,py,mode,
                            clip_mode,Clip(*custom),Clip(*custom))
        assert valid==int(clipped is not None and not (weighted and amount==0)),(sw,sh,mode,px,py,clipped,valid)
        assert bytes(dst)==expected,(scaled_index,sw,sh,mode,px,py,weighted,effect,amount,clipped)
    weighted_cases=20000
    for _ in range(weighted_cases):
        source,destination,amount=rng.randrange(2**32),rng.randrange(2**32),rng.randrange(101)
        oracle.cpu.mem_write(BLOCKS,struct.pack("<I",source))
        oracle.cpu.mem_write(BLOCKS+16,struct.pack("<I",destination))
        for address,value in ((0x5BB764,BLOCKS),(0x5BB768,BLOCKS+16),
                (0x55F1F0,0x558CF0+amount*256),(0x55F1F4,0x558CF0+(100-amount)*256)):
            oracle.cpu.mem_write(address,struct.pack("<I",value))
        oracle.call(0x4902A0)
        expected=struct.unpack("<I",oracle.cpu.mem_read(BLOCKS+16,4))[0]
        result=ctypes.c_uint32()
        assert native.vertrix_render_weighted_pixel(source,destination,amount,ctypes.byref(result))
        assert result.value==expected
    result=ctypes.c_uint32(123)
    assert not native.vertrix_render_weighted_pixel(0,0,101,ctypes.byref(result))
    assert result.value==123
    report={"scaled_alpha_override_dispatch_cases_verified":3000,"prepared_original_dispatch_cases_verified":7000,"unscaled_original_dispatch_cases_verified":1000,"unscaled_premultiplied_dispatch_cases_verified":333,"scaled_weighted_sprite_draws_verified":2000,"sampled_weighted_rectangles_verified":1000,"weighted_pixel_cases_verified":weighted_cases,"percentage_table_entries_verified":25856,"sampled_effect_rectangles_verified":2000,"scaled_binary_sprite_draws_verified":1000,"scaled_effect_sprite_draws_verified":2000,"scaled_clipped_sprite_draws_verified":scaled_draws,"scale_advance_bytes_verified":15360,"sampled_rectangles_verified":sampled_rectangles,"sampled_rows_verified":sampled_rows,"binary_alpha_rectangles_verified":copy_cases,"clipped_sprite_draws_verified":draw_cases,"transparent_rectangles_verified":copy_cases,"alpha_table_entries_verified":65536,"opaque_rectangles_verified":copy_cases,"effect_pixel_cases_verified":effect_cases,"direct_pixel_cases_verified":direct_cases,"status":"passed","offset_cases_verified":10000,"pixel_read_write_cases_verified":6000,
            "scope":"Original 0x478eb0, 0x478f10 and 0x478ed0 execute unchanged for addressing and 1/2/4-byte little-endian pixels. Direct kernels 0x48d720, 0x49b4a0, 0x4933e0 and 0x4a3540 also execute unchanged; Seven 32-bit amount-50 effect kernels also execute unchanged; Opaque rectangle traversal 0x4ab310 also executes unchanged; Transparent traversal 0x4ab380 and alpha table initializer also execute unchanged; Binary alpha traversal 0x4ab2a0 also executes unchanged; Horizontal sampler 0x492710 executes unchanged with direct kernel 0x48d720; Vertical sampler 0x4928f0 executes unchanged with horizontal sampler 0x492710; Binary sampling 0x492550 also executes unchanged. Scaled clipped sprites compose original measurement, clipping and alignment, then execute the complete original 0x4af560 dispatcher with prepared renderer globals, alternating opaque and binary-alpha traversal. Half of scaled fixtures also set object +0x150; scale traversal group two bypasses the special alpha table and falls back to ordinary selected kernels. Unscaled sprites also execute the full dispatcher, with object +0x150 nonzero selecting premultiplied alpha. Border, callbacks, resource setup and presentation remain outside this comparison."}
    (args.build_dir/"surface-verification.json").write_text(json.dumps(report,indent=2)+"\n")
    print(json.dumps(report,indent=2))

if __name__=="__main__":
    main()
