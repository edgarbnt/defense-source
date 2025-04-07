/*
** EPITECH PROJECT, 2024
** amazed
** File description:
** amazed
*/

#include "../include/my.h"

static char eval_links(link_t **step_next, link_t *links, int score)
{
    for (link_t *room = links; room; room = room->next) {
        if (room->link->score < score)
            continue;
        if (!add_link(step_next, room->link))
            return 0;
        room->link->score = score;
    }
    return 1;
}

char eval_scores(room_t *end)
{
    link_t *step_cur = NULL;
    link_t *step_next = NULL;
    int ret = 1;

    end->score = 0;
    if (!add_link(&step_cur, end))
        return 0;
    for (int score = 1; step_cur; step_cur = step_next) {
        step_next = NULL;
        for (link_t *room = step_cur; ret && room; room = room->next)
            ret = eval_links(&step_next, room->link->links, score);
        if (!ret)
            return 0;
        free_links(step_cur);
        score++;
    }
    return 1;
}
