#include "Cluster.h"
#include <cmath>
#include <cassert>
#include <tuple>

size_t Cluster::getWidth() const {
    return _width;
}

size_t Cluster::getHeight() const {
    return _height;
}

Cluster::~Cluster() {
    delete &Cluster::instance();
}

const std::tuple<size_t, int, int> &Cluster::operator()(size_t x, size_t y) const {
    return _cluster[x][y];
}

void Cluster::init(size_t processNumber, size_t root) {
    size_t height = processNumber / sqrt(static_cast<int>(processNumber));
    size_t width = processNumber / height;
    assert(width * height <= processNumber);
    init(processNumber, root, height, width);
}

Cluster &Cluster::instance() {
    static Cluster *_instance;
    if (_instance == nullptr) {
        _instance = new Cluster();
    }
    return *_instance;
}

void Cluster::init(size_t processNumber, size_t root, size_t height, size_t width) {
    if (_initialized) {
        throw std::runtime_error("cluster is already initialized");
    }

    assert(height * width == processNumber);
    _processNumber = processNumber;
    _root = root;
    _height = height;
    _width = width;
    _initClusterModelHolder();
}

void Cluster::_initClusterModelHolder() {
    _cluster.resize(_height);
    for (int i = 0; i < _height; ++i) {
        _cluster[i].resize(_width);
    }
    _cluster[0][0] = {_root, 0, _height};
    size_t inx = 0;
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            if (inx == _root) { ++inx; }
            if (i == 0 && j == 0) continue;
            _cluster[i][j] = {inx, i, _height + j};
            ++inx;
        }
    }
}

size_t Cluster::getRoot() const {
    return _root;
}

std::ostream &operator<<(std::ostream &os, const Cluster &cluster) {
    os << "\t*";
    for (size_t i = 0; i < cluster.getHeight(); ++i) {
        for (size_t j = 0; j < cluster.getWidth(); ++j) {
            std::cout << cluster(i, j) << " ";
        }
        if (i != cluster.getHeight() - 1) {
            std::cout << std::endl << "\t ";
        }
    }
    return os;
}