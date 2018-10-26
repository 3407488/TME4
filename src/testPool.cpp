#include <iostream>
#include <vector>

#include "Pool.h"
#include "JobConcret.h"
#include "Barrier.h"

int main(void) {

    int N = 300;

    pr::Pool p(N);
    p.start(8);

    pr::Barrier barrier(N);

    std::vector<int> vecRes(N, 0);

    for (int i = 0; i < N; i++) {
        p.submit(new pr::JobConcret(i, &vecRes[i], &barrier));
    }

    barrier.waitFor();

    return 0;
}