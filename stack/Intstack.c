#include <IntStack.h>

int initialize (Intstack *s,int max) {
    s->ptr = 0;
    if ((s->max = max) > 0) {
        if ((s->stk = malloc(sizeof(int)*max)) == NULL) {
            s->max = 0;
        }
    }
    return s->max;
}
