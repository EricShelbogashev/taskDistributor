#include "src/model/MatrixTask.h"

int main(int argc, char **argv) {
    /* Non-parallel section.  */
    MatrixTask container(argc, argv);
    container.execute();
    /* Non-parallel section.  */
    return 0;
}
