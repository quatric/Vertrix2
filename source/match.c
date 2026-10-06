#include "game.h"
#include <string.h>
/* Coordinates and rewards checked against the original x86 figure routine. */
const Figure figures[9] = {{7, 7, {-1, 1, -2, 0, 2, -1, 1}, {-1, -1, 0, 0, 0, 1, 1}},
                           {5, 6, {0, -1, 0, 1, 0}, {-1, 0, 0, 0, 1}},
                           {5, 5, {-1, 1, 0, -1, 1}, {-1, -1, 0, 1, 1}},
                           {5, 4, {-1, 0, 1, 0, -1}, {-2, -1, 0, 1, 2}},
                           {5, 4, {-2, -1, 0, 1, 2}, {1, 0, -1, 0, 1}},
                           {5, 4, {1, 0, -1, 0, 1}, {-2, -1, 0, 1, 2}},
                           {5, 4, {-2, -1, 0, 1, 2}, {-1, 0, 1, 0, -1}},
                           {5, 3, {-2, -1, 0, 1, 2}, {0, 0, 0, 0, 0}},
                           {4, 2, {0, -1, 1, 0}, {-1, 0, 0, 1}}};
static int inside(int x, int y)
{
    return x >= 0 && x < COLS && y >= 0 && y < ROWS;
}
/* Original 0x434ee0 (answer in eax: any figure found; the reward word through its stack pointer;
 * the mask only when ecx is 1). The reward counts a figure when none of its cells was already
 * marked. */
/* The original checks the figures in this order: the fifth shape comes before the fourth, which
 * decides which of two overlapping weight-four figures earns its reward. */
static const int FIGURE_ORDER[9] = {0, 1, 2, 3, 5, 4, 6, 7, 8};
/* The brand the original writes into every cell of an accepted figure. */
enum
{
    FIGURE_BRAND = 7
};

int vertrix_figure_pass(uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS], int *reward,
                        int commit)
{
    int found = 0;
    int overlap[COLS][ROWS];
    int branded[COLS][ROWS];
    *reward = 0;
    memset(overlap, 0, sizeof overlap);
    memset(branded, 0, sizeof branded);
    for (int order = 0; order < 9; order++)
        for (int x = 0; x < COLS; x++)
            for (int y = 0; y < ROWS; y++)
            {
                const Figure *s = &figures[FIGURE_ORDER[order]];
                int color = -1, ok = 1, used = 0;
                for (int i = 0; i < s->n; i++)
                {
                    int xx = x + s->dx[i], yy = y + s->dy[i];
                    int cell;
                    if (!inside(xx, yy))
                    {
                        ok = 0;
                        break;
                    }
                    cell = board[xx][yy];
                    if (cell == EMPTY || cell == STONE || cell == BOMB)
                    {
                        ok = 0;
                        break;
                    }
                    if (color < 0)
                        color = cell;
                    if ((int)(int8_t)cell != color)
                    {
                        ok = 0;
                        break;
                    }
                    used += overlap[xx][yy] != 0;
                }
                if (ok)
                {
                    int i;
                    found = 1;
                    for (i = 0; i < s->n; i++)
                    {
                        int xx = x + s->dx[i], yy = y + s->dy[i];
                        if (commit)
                        {
                            mask[xx][yy] = 1;
                            branded[xx][yy] = 1;
                        }
                        overlap[xx][yy] = 1;
                    }
                    if (!used)
                        *reward += s->weight;
                }
            }
    if (commit)
    {
        for (int x = 0; x < COLS; x++)
        {
            for (int y = 0; y < ROWS; y++)
            {
                if (branded[x][y])
                    board[x][y] = FIGURE_BRAND;
            }
        }
    }
    return found;
}

int vertrix_line_pass(const uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS], int threshold,
                      int *reward)
{
    uint8_t scan[COLS][ROWS];
    memcpy(scan, board, sizeof scan);
    const int dx[6] = {1, 0, 1, 1, -1, -1}, dy[6] = {0, 1, 1, 1, 1, 1};
    int found = 0;
    for (int pass = 0; pass < 6; pass++)
    {
        int starts = (pass == 0 || pass == 2 || pass == 4) ? ROWS : COLS;
        for (int start = 0; start < starts; start++)
        {
            int x = pass == 0 || pass == 2 ? 0 : pass == 4 ? COLS - 1 : start;
            int y = pass == 0 || pass == 2 || pass == 4 ? start : 0;
            int n = 0, color = EMPTY;
            for (; inside(x, y); x += dx[pass], y += dy[pass])
            {
                if (scan[x][y] == EMPTY || scan[x][y] == STONE || scan[x][y] == BOMB)
                {
                    color = scan[x][y];
                    n = 0;
                    continue;
                }
                if (scan[x][y] != color)
                {
                    color = scan[x][y];
                    n = 1;
                    continue;
                }
                n++;
                if (n <= threshold)
                    continue;
                int used = 0;
                for (int i = 0; i < n; i++)
                    used += mask[x - i * dx[pass]][y - i * dy[pass]] != 0;
                for (int i = 0; i < n; i++)
                    mask[x - i * dx[pass]][y - i * dy[pass]] = 1;
                if (!used)
                {
                    *reward += 1;
                    found = 1;
                }
            }
        }
    }
    return found;
}

int match_board(uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS], int threshold, int use_figures)
{
    int reward = 0;
    memset(mask, 0, COLS * ROWS);
    if (use_figures)
    {
        uint8_t branded[COLS][ROWS];
        /* The executable keeps a separate unmodified board for the line pass. */
        memcpy(branded, board, sizeof branded);
        vertrix_figure_pass(branded, mask, &reward, 1);
    }
    vertrix_line_pass(board, mask, threshold, &reward);
    return reward;
}
