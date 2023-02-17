#ifndef TASKDISTRIBUTOR_CLUSTER_H
#define TASKDISTRIBUTOR_CLUSTER_H

#include <iostream>
#include <vector>
#include "../utils/PrettyPrint.h"

class Cluster {
public:
    static Cluster &instance();

    ~Cluster();

    [[nodiscard]] size_t getHeight() const;

    [[nodiscard]] size_t getWidth() const;

    void init(size_t processNumber, size_t root);

    void init(size_t processNumber, size_t root, size_t height, size_t width);

    size_t getRoot() const;

    const std::tuple<size_t, int, int> &operator()(size_t x, size_t y) const;

    Cluster(const Cluster &other) = delete;

protected:
    explicit Cluster() = default;

    void _initClusterModelHolder();
    size_t _processNumber;
    size_t _root;
    size_t _height = 0;
    size_t _width = 0;
    std::vector<std::vector<std::tuple<size_t, int, int>>> _cluster;
    bool _initialized = false;
};

std::ostream &operator<<(std::ostream &os, const Cluster &cluster);

#endif //TASKDISTRIBUTOR_CLUSTER_H
