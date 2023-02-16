#include "Cluster.h"
#include <cmath>
#include <cassert>

Cluster::Cluster(size_t processNumber, size_t root, size_t height, size_t width) :
        _processNumber(processNumber),
        _root(root),
        _height(height),
        _width(width),
        _cluster(height) {
}

size_t Cluster::getWidth() const {
    return _width;
}

size_t Cluster::getHeight() const {
    return _height;
}

Cluster::~Cluster() {
    delete instance;
}

Cluster &Cluster::init(size_t processNumber, size_t root) {
    if (instance == nullptr) {
        size_t height = processNumber / sqrt(static_cast<int>(height));
        size_t width = processNumber / height;
        assert(width * height <= processNumber);
        instance = new Cluster(processNumber, root, height, width);
    }
    return *instance;
}

void Cluster::_initCluster() {
    for (int i = 0; i < _height; ++i) {
        _cluster[i].resize(_width);
    }
    _cluster[0][0] = _root;
    size_t inx = 0;
    for (int i = 0; i < _height; ++i) {
        for (int j = 0; j < _width; ++j) {
            if (inx == _root) { ++inx; }
            _cluster[i][j] = inx;
            ++inx;
        }
    }
}

size_t Cluster::operator()(size_t x, size_t y) const {
    return _cluster[x][y];
}

