#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "matchTimeline.h"

/* ============================================================================
STRUCTS
============================================================================ */

/*
 typedef enum {Home, Away} team;

 typedef enum {Goal, YellowCard, RedCard} event;

 El tiempovaaserrepresentadoporununsignedint,quesecorrespondeconel
 minutoenelquesucedióelevento,esdecirunnúmeroentre0y90(nosetienenen
 cuentatiemposadicionales)

  Elnúmerodejugadorvaaserrepresentadoporununsignedint,yparasimplificar,
 vamosaasumirquecadaequipoutilizaalosjugadoresconnúmerosentreel1yel
 11

 Lafunción“matchTimeline_get_score”devuelveel resultadodelpartido,perodeaun
 equipoalavez,esdecirsiselepasacomoatributoHomedevuelvelosgolesdelequipo
 local,ysiselepasacomoatributoAway, losgolesdelequipovisitante.ESTEMÉTODO
 DEBESERCONSTANTE!

  En “matchTimeline_is_time_and_score_valid” sedebechequearlassiguientes
 condiciones:
 ● Loseventosdebenestarenordencronológico
 ● LacantidaddegolesquetieneHomesedebecorresponderalacantidadde
 registrosconequipoHome
 ● LacantidaddegolesquetieneAwaysedebecorresponderalacantidadde
 registrosconequipoAway
*/

struct s_node
{
    team team;
    event e;
    time t;
    playerNumber pn;
    struct s_node *next;
};

struct s_matchTimeline
{
    struct s_node *head;
    unsigned int counterHome;
    unsigned int counterAway;
    unsigned int sizemt;
    // COMPLETAR
};

/* ============================================================================
INVERP & VALIDATION
============================================================================ */

static bool invrep(matchTimeline mt)
{
    bool valid = true;
    if (mt != NULL){
        if (mt->head != NULL){
            struct s_node *iter = mt->head;
            while (iter != NULL){
                if (iter->t > 90){
                    valid = false;
                }
                iter = iter->next;
            }            
        }
    }
    return valid;
}

bool matchTimeline_is_time_and_score_valid(matchTimeline mt)
{
    bool valid_score = true;
    bool valid_time = true;
    unsigned int c_home = 0u;
    unsigned int c_away = 0u;
    if (mt != NULL){
        if (mt->head != NULL){
            struct s_node *iter_time = mt->head;
            while (iter_time->next != NULL){
                    if (iter_time->t > iter_time->next->t){
                        valid_time = false;
                    }
                    iter_time = iter_time->next;
            }            
            struct s_node *iter = mt->head;
            while (iter != NULL){
                if (iter->e == Goal && iter->team == Home){
                    c_home++;
                } else if (iter->e == Goal && iter->team == Away){
                    c_away++;
                }
                iter = iter->next;
            }
            if (c_home != mt->counterHome){
                valid_score = false;
            }
            if (c_away != mt->counterAway){
                valid_score = false;
            }
        }
    }
    return valid_score && valid_time;
}

/* ============================================================================
CONSTRUCTOR
============================================================================ */

matchTimeline matchTimeline_empty(void)
{
    matchTimeline mt = NULL;
    mt = malloc(sizeof(struct s_matchTimeline));
    mt->counterAway = 0u;
    mt->counterHome = 0u;
    mt->sizemt = 0u;
    mt->head = NULL;
    assert(invrep(mt));
    return mt;
}

/* ============================================================================
INSERTION
============================================================================ */

static struct s_node *create_node(team team, event e, time t, playerNumber pn)
{

    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));

    new_node->team = team;
    new_node->e = e;
    new_node->t = t;
    new_node->pn = pn;
    new_node->next = NULL;

    assert(new_node != NULL);

    return new_node;
}

/* ============================================================================
GOAL
============================================================================ */

static bool red_player (matchTimeline mt, playerNumber pn, team team){
    bool red = false;
    if (mt != NULL){
        if (mt->head != NULL){
            struct s_node *iter = mt->head;
            while (iter != NULL && !false){
                if (iter->e == RedCard && iter->pn == pn && iter->team == team){
                    red = true;
                }
                iter = iter->next;
            }
        }
    }
    return red;
}

matchTimeline matchTimeline_score_goal(matchTimeline mt, team team, time t, playerNumber pn){
    assert(invrep(mt));
    if (mt != NULL){
        if (t <= 90){
            if (red_player(mt,pn,team)==false){
                struct s_node *new_goal = create_node(team,Goal,t,pn);
                if (team == Home){
                    mt->counterHome++;
                } else if (team == Away){
                    mt->counterAway++;
                }
                if (mt->head != NULL){
                    struct s_node *iter = mt->head;
                    while (iter->next != NULL){
                        iter = iter->next;
                    }
                    iter->next = new_goal;
                } else {
                    mt->head = new_goal;
                }
                mt->sizemt++;
                }
            }
    }
    return mt;
}

/* ============================================================================
THE CARDS
============================================================================ */

matchTimeline matchTimeline_receive_yellowCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    if (mt!=NULL){
        if (t <= 90){
            if (mt->head != NULL){
                struct s_node *iter = mt->head;
                unsigned int counter_yellowcard = 0u;
                while (iter != NULL){
                    if (iter->e == YellowCard && iter->pn == pn){
                        counter_yellowcard++;
                    }
                    iter = iter->next;
                }
                if (counter_yellowcard == 1){
                    mt = matchTimeline_receive_redCard(mt,team,t,pn);
                } else {
                    struct s_node *even_yellow = create_node(team, YellowCard, t, pn);
                    struct s_node *iter = mt->head;
                    while (iter->next != NULL){
                        iter = iter->next;
                    }
                    iter->next = even_yellow;
                
                }
                mt->sizemt++;
            } else {
                struct s_node *even_yellow = create_node(team, YellowCard, t, pn);
                mt->head = even_yellow;
                mt->sizemt++;
            }
        }
    }
    return mt;
}

matchTimeline matchTimeline_receive_redCard(matchTimeline mt, team team, time t, playerNumber pn)
{
    assert(invrep(mt));
    if (mt!=NULL){
        if (t <= 90){
            struct s_node *event_red = create_node(team, RedCard, t, pn); 
            if (mt->head != NULL){
                struct s_node *iter = mt->head;
                while (iter->next != NULL){
                    iter = iter->next;
                }
                iter->next = event_red;
            } else {
                mt->head = event_red;
            }
            mt->sizemt++;   
        }
    }
    return mt;
}

/* ============================================================================
SCORE
============================================================================ */

unsigned int matchTimeline_get_score(matchTimeline mt, team team)
{
    assert(invrep(mt));
    unsigned int score = 0u;
    if (team == Home){
        score = mt->counterHome;
    } else if (team == Away){
        score = mt->counterAway;
    }
    return score;
}

/* ============================================================================
SIZE
============================================================================ */

unsigned int matchTimeline_size(matchTimeline mt)
{
    assert(invrep(mt));
    unsigned int size = mt->sizemt;
    return size;
}

/* ============================================================================
PRINT
============================================================================ */

void matchTimeline_print(matchTimeline mt)
{
    fprintf(
        stdout, "            Home %u -  %u Away \n", 
        matchTimeline_get_score(mt, Home), 
        matchTimeline_get_score(mt, Away)
    );

    struct s_node *aux = mt->head;
    while (aux != NULL)
    {
        unsigned int t = aux->t;
        char *e;
        switch (aux->e)
        {
        case Goal:
            e = "    Goal   ";
            break;
        case YellowCard:
            e = "Yellow Card";
            break;
        case RedCard:
            e = "  Red Card ";
            break;
        }
        unsigned int pn = aux->pn;

        if (aux->team == Home) {
            fprintf(stdout, "%u - %s - %u' \n", pn, e, t);
        }
        else {
            fprintf(stdout, "                   %u' - %s - %u \n", t, e, pn);
        }

        aux = aux->next;
    }
}

/* ============================================================================
ARRAY
============================================================================ */

event *matchTimeline_events_array(matchTimeline mt)
{
    event *array = NULL;
    array = calloc(matchTimeline_size(mt),sizeof(event));
    if (mt->head != NULL){
        struct s_node *iter = mt->head;
        for (unsigned int i = 0; i < matchTimeline_size(mt) && iter != NULL; i++){
            array[i] = iter->e;
            iter = iter->next;
        }
    }
    return array;
}

/* ============================================================================
DESTRUCTOR!
============================================================================ */

static struct s_node *destroy_node(struct s_node *node)
{
    node->next = NULL;
    free(node);
    return node;
}

matchTimeline matchTimeline_destroy(matchTimeline mt)
{
    assert(invrep(mt));
    if (mt != NULL){
        struct s_node *iter = mt->head;
        while (iter != NULL){
            struct s_node *next = iter->next;
            destroy_node(iter);
            iter = next;
        }
        free(mt);
        mt = NULL;
    }
    return mt;
}
