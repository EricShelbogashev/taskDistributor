#ifndef TASKDISTRIBUTOR_CLUSTER_H
#define TASKDISTRIBUTOR_CLUSTER_H

#include <iostream>
#include <vector>

class Cluster {
public:

    static Cluster &init(size_t processNumber, size_t root);

    ~Cluster();

    [[nodiscard]] size_t getHeight() const;

    [[nodiscard]] size_t getWidth() const;

    size_t operator()(size_t x, size_t y) const;

protected:
    explicit Cluster() = delete;

    explicit Cluster(size_t processNumber, size_t root, size_t height, size_t width);
    Cluster(const Cluster &other) = delete;
    void _initCluster();
    static Cluster *instance;

    size_t _processNumber;
    size_t _root;
    size_t _height = 0;
    size_t _width = 0;
    std::vector<std::vector<size_t>> _cluster;
};

std::ostream &operator<<(std::ostream &os, const Cluster &cluster) {
    return os;
}

#endif //TASKDISTRIBUTOR_CLUSTER_H
