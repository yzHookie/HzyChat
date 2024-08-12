#include "util.h"

namespace util {
void repolish(QWidget *w) {
    w->style()->unpolish(w);
    w->style()->polish(w);
};
}

