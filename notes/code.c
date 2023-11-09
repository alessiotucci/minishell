#include <stdio.h> 
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>

// This function stores a character in the word array and increments the word counter
bool store_char(char *word, size_t max_word, int c, size_t *wordn)
{
    if (*wordn < max_word - 1)
    {
        word[(*wordn)++] = c;
        return true;
    }
    else
    {
        return false;
    }
}

// This function handles the GTGT state
TOKEN handle_gtgt_state(int c)
{
    if (c == '>')
    {
        return T_GTGT;
    }
    ungetc(c, stdin);
    return T_GT;
}

// This function handles the INQUOTE state
TOKEN handle_inquote_state(char *word, size_t max_word, size_t *wordn, int c)
{
    switch (c)
    {
        case '\\':
            if ((c = getchar()) == EOF)
                c = '\\';
            ec_false( store_char(word, max_word, c, wordn) );
            continue;
        case '"':
            ec_false( store_char(word, max_word, '\0', wordn) );
            return T_WORD;
        default:
            ec_false( store_char(word, max_word, c, wordn) );
            continue;
    }
}

// This function handles the INWORD state
TOKEN handle_inword_state(char *word, size_t max_word, size_t *wordn, int c)
{
    switch (c)
    {
        case ';':
        case '&':
        case '|':
        case '<':
        case '>':
        case '\n':
        case ' ':
        case '\t':
            ungetc(c, stdin);
            ec_false( store_char(word, max_word, '\0', wordn) );
            return T_WORD;
        default:
            ec_false( store_char(word, max_word, c, wordn) );
            continue;
    }
}

// This function handles the NEUTRAL state
TOKEN handle_neutral_state(char *word, size_t max_word, size_t *wordn, int c, int *state)
{
    switch (c)
    {
        case ';':
            return T_SEMI;
        case '&':
            return T_AMP;
        case '|':
            return T_BAR;
        case '<':
            return T_LT;
        case '\n':
            return T_NL;
        case ' ':
        case '\t':
            continue;
        case '>':
            *state = GTGT;
            continue;
        case '"':
            *state = INQUOTE;
            continue;
        default:
            *state = INWORD;
            ec_false( store_char(word, max_word, c, wordn) );
            continue;
    }
}

// This function gets the token
TOKEN get_token(char *word, size_t max_word)
{
    enum {NEUTRAL, GTGT, INQUOTE, INWORD} state = NEUTRAL;
    int c;
    size_t wordn = 0;
    while ((c = getchar()) != EOF)
    {
        switch (state)
        {
            case NEUTRAL:
                return handle_neutral_state(word, max_word, &wordn, c, &state);
            case GTGT:
                return handle_gtgt_state(c);
            case INQUOTE:
                return handle_inquote_state(word, max_word, &wordn, c);
            case INWORD:
                return handle_inword_state(word, max_word, &wordn, c);
        }
    }
}

