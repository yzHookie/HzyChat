#include "global.h"

namespace global {
void repolish(QWidget *w) {
    w->style()->unpolish(w);
    w->style()->polish(w);
};
}

