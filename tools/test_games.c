/* Each game's archive is recognized as that game's and only that one.
 *
 * usage: test_games VERTRIX2_VF VERTRIX3_VF [VERTRIX2_V12_VF] */
#include <stdio.h>

#include "games.h"

int main(int argc, char **argv)
{
    if (argc != 3 && argc != 4)
    {
        fprintf(stderr, "usage: test_games VERTRIX2_VF VERTRIX3_VF [VERTRIX2_V12_VF]\n");
        return 2;
    }
    static const VertrixGameId expected_ids[] = {VERTRIX_GAME_2, VERTRIX_GAME_3,
                                                 VERTRIX_GAME_2_V12};
    int failed = 0;
    for (int i = 0; i < argc - 1; ++i)
    {
        VertrixVf *archive = vertrix_vf_open(argv[1 + i]);
        const VertrixGame *game = archive ? vertrix_game_of_archive(archive) : NULL;
        const VertrixGame *expected = vertrix_game(expected_ids[i]);
        printf("%s: %s\n", argv[1 + i], game ? game->title : "not recognized");
        failed |= game != expected;
        vertrix_vf_close(archive);
    }
    failed |= vertrix_game(VERTRIX_GAME_COUNT) != NULL || vertrix_game_of_archive(NULL) != NULL;
    puts(failed ? "FAILED" : "passed");
    return failed;
}
