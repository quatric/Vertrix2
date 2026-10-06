# Wii original archive access

`source/wii_archive.c` mounts the internal Wii SD interface under `sd` and opens the original archive at `sd:/apps/vertrix2/Vertrix2.vf`. Archive entries are read through the existing read-only VF loader without extracting or rewriting files.

Initialize `VertrixWiiArchive` to zero. Call `vertrix_wii_archive_open` once during application startup, retain the handle while asset loaders need it, and call `vertrix_wii_archive_close` at shutdown. Startup must own this mount exclusively. An open failure releases the acquired mount; shutdown closes the archive before unmounting. Separate result codes distinguish invalid ownership state, mounting failure and archive opening failure.

Build with `make wii-archive`. Final application linkage needs the resulting archive library plus `-lfat -logc -lm`, Wii libogc library paths and `-mrvl`. The installed libfat headers require `__wii__` in addition to the existing platform defines. A small scratch program referencing both open and close successfully linked to a PowerPC Wii ELF against the installed SDK. Source formatting checks passed.

This is the archive lifecycle module, not the full application entry point. It has not been executed on hardware or Dolphin. SD mounting, runtime reads and shutdown therefore remain unverified on Wii; the VF parser itself has separate host verification against the original archive.
