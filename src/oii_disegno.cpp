/*
 * @author: Lorenzo Ferrari
 * solution of "disegno".
 *
 * The fundamental entities are the intersection (struct Node). Segments are
 * edges in the graph of all the intersections.
 *
 * Functions:
 *  * remove(Point O)
 *      undo the move of a cross in O (assume the move is legal) and update
 *      the structures consequently
 *  * free_square(Point bottom_left, Point top_right)
 *      exactly what you would expect, see the implementation for reference
 *  * free_until_move(Point bottom_left)
 *      consider the free square having bottom_left as a vertex. If the grid is
 *      valid, the corner opposite to bottom_left is the center of some move.
 *      
 * Steps:
 *  * manually add the segments on the boundary
 *  * for each intersection, keep pointers to its neighbours in the 4 directions
 *  * keep a set of all the free squares currently in the grid. Note that such
 *    a set uniquely identifies a grid and every valid grid can be expressed as
 *    union of empty squares.
 *  * while (0;0);(L;L) is not free, there is more than one free square in the grid, call
 *    free_until_move({0,0})
 *
 *
 * The running time is linear in the number of calls to free_until_move, which
 * is linear in the number of moves, hence linear in the input.
 * Time complexity: O(N log N)
 * Space complexity: O(N)
 */

#include <set>
#include <map>
#include <array>
#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>

#include "disegno.h"

using namespace std;

// just operators. can possibly be moved to disegno.h
bool operator<(const Point& A, const Point& B) {
    return pair(A.x, A.y) < pair(B.x, B.y);
}
bool operator==(const Point& A, const Point& B) {
    return A.x == B.x && A.y == B.y;
}
bool operator!=(const Point& A, const Point& B) {
    return !(A == B);
}
ostream& operator<<(ostream& os, const Point& A) {
    return os << '(' << A.x << ',' << A.y << ')';
}

// fundamental entity
struct Node {
    int x, y;
    Node* u = nullptr;
    Node* r = nullptr;
    Node* d = nullptr;
    Node* l = nullptr;
};

constexpr int MAXN = 5000000;
static Node nodes[MAXN];
vector<Point> moves;            // answer
vector<Point> points;           // points sorted by coordinates
set<array<Point, 2>> empty_squares;

Node* coord_to_node(int x, int y) {
    Point pt{x, y};
    auto it = lower_bound(begin(points), end(points), pt);
    if (it == end(points) || *it != pt) {
        return nullptr;
    }
    return nodes + (it - begin(points));
};

// determine whether a rectangle is free
bool is_free(Point bottom_left, Point top_right) {
    return empty_squares.count({bottom_left, top_right});
}

void add_edge(Node* a, Node* b) {
    // assume (a->x,a->y) < (b->x,b->y)
    if (a->x == b->x) {
        a->u = b;
        b->d = a;
    } else if (a->y == b->y) {
        a->r = b;
        b->l = a;
    }
}

void remove(Node* n) {
    assert(n->u && n->r && n->d && n->l);   // a cross is a cross
    int x1 = n->l->x;
    int x2 = n->r->x;
    int y1 = n->d->y;
    int y2 = n->u->y;
    array<array<Point, 2>, 4> quadrants {
        array{Point{x1, y1}, Point{n->x, n->y}},
        array{Point{x1, n->y}, Point{n->x, y2}},
        array{Point{n->x, n->y}, Point{x2, y2}},
        array{Point{n->x, y1}, Point{x2, n->y}}
    };
    for (auto [p1, p2] : quadrants) {
        assert(is_free(p1, p2));
        empty_squares.erase({p1, p2});
    }

    // detach n from its neighbours
    n->u->d = nullptr;
    n->r->l = nullptr;
    n->d->u = nullptr;
    n->l->r = nullptr;

    // some projections are no longer intersections once the cross is removed
    auto fix_projection = [&](Node* p) -> void {
        if (p->u && p->d && !(p->r || p->l)) {
            p->u->d = p->d; p->d->u = p->u;
            p->u = p->r = p->d = p->l = nullptr;
        } else if (p->r && p->l && !(p->u || p->d)) {
            p->r->l = p->l; p->l->r = p->r;
            p->u = p->r = p->d = p->l = nullptr;
        }
    };
    if (n->u) fix_projection(n->u);
    if (n->r) fix_projection(n->r);
    if (n->d) fix_projection(n->d);
    if (n->l) fix_projection(n->l);

    moves.push_back({n->x, n->y});
    empty_squares.insert({Point{x1,y1}, Point{x2,y2}});
    n->u = n->r = n->d = n->l = nullptr;
}

bool free_square(Node*, Node*);

// in general, if you are dereferencing a nullptr the grid is not valid
// return false only if the grid is not valid
bool free_until_move(Node* bottom_left) {
    // assume the rectangle bottom_left,center is free
    if (bottom_left->r == nullptr) return false;
    if (bottom_left->u == nullptr) return false;
    if (bottom_left->r->u == nullptr) return false;
    if (bottom_left->u->r == nullptr) return false;
    while (bottom_left->r->u->y != bottom_left->u->y) {
        bool ret = free_until_move(bottom_left->r);
        if (!ret) return false;
    }
    while (bottom_left->u->r->x != bottom_left->r->x) {
        bool ret = free_until_move(bottom_left->u);
        if (!ret) return false;
    }
    // in a valid grid, the calls to free_until_move result in three squares in
    // the shape of an L
    Node* center = bottom_left->r->u;
    assert(center == bottom_left->u->r);
    if (bottom_left->r->r == nullptr) return false;
    if (bottom_left->u->u == nullptr) return false;
    int x = bottom_left->r->r->x;
    int y = bottom_left->u->u->y;

    bool ret = free_square(center, coord_to_node(x, y)); // free the 4th quadrant
    if (!ret) return false;

    // now that the quandrants are free, make the move
    remove(center);

    return true;
}

// return false only if the grid is not valid
bool free_square(Node* bottom_left, Node* top_right) {
    if (bottom_left == nullptr) return false;   // if the grid is not valid, without
    if (top_right == nullptr) return false;     // these if there is a runtime error
    while (true) {
        int x1 = bottom_left->x;
        int y1 = bottom_left->y;
        int x2 = top_right->x;
        int y2 = top_right->y;
        if (is_free(Point{x1, y1}, Point{x2, y2})) {
            break;
        }
        bool ret = free_until_move(bottom_left);
        if (!ret) return false;
    }
    return true;
}

vector<Point> draw(int N, int L, vector<Point> A, vector<Point> B) {
    points.push_back({0,0});
    points.push_back({0,L});
    points.push_back({L,0});
    points.push_back({L,L});
    for (int i = 0; i < N; ++i) {
        points.push_back(A[i]);
        points.push_back(B[i]);
    }
    sort(begin(points), end(points));
    points.erase(unique(begin(points), end(points)), end(points));

    // map each pair (x;y) to a Node
    for (int i = 0; i < (int)points.size(); ++i) {
        nodes[i].x = points[i].x;
        nodes[i].y = points[i].y;
    }

    for (int i = 0; i < N; ++i) {
        assert(A[i] < B[i] && "input does not respect constraints");
        Node* a = coord_to_node(A[i].x, A[i].y);
        Node* b = coord_to_node(B[i].x, B[i].y);
        add_edge(a, b);
    }

    {
        // add the edges on the boundary, nothing interesting
        array<int, 2> extremes{0, L};   
        for (int extreme_value : extremes) {
            vector<int> xs, ys;
            for (Point pt : points) {
                if (pt.y == extreme_value) xs.push_back(pt.x);
                if (pt.x == extreme_value) ys.push_back(pt.y);
            }
            sort(begin(xs), end(xs));
            sort(begin(ys), end(ys));
            xs.erase(unique(begin(xs), end(xs)), end(xs));
            ys.erase(unique(begin(ys), end(ys)), end(ys));
            for (int i = 1; i < (int)xs.size(); ++i) {
                Node* a = coord_to_node(xs[i - 1], extreme_value);
                Node* b = coord_to_node(xs[i    ], extreme_value);
                assert(a && b && "points should exist");
                add_edge(a, b);
            }
            for (int i = 1; i < (int)ys.size(); ++i) {
                Node* a = coord_to_node(extreme_value, ys[i - 1]);
                Node* b = coord_to_node(extreme_value, ys[i    ]);
                assert(a && b && "points should exist");
                add_edge(a, b);
            }
        }
    }

    // the graph is now built

    // find the empty squares
    for (int i = 0; i < (int)points.size(); ++i) {
        Node* a = nodes + i;
        Node* b = nodes + i;
        if (a->r == nullptr) continue;
        if (b->u == nullptr) continue;
        a = a->r;
        b = b->u;
        while (a->u == nullptr && a->r) a = a->r;
        while (b->r == nullptr && b->u) b = b->u;
        if (a->u == nullptr) continue;
        if (b->r == nullptr) continue;
        a = a->u;
        b = b->r;
        while (a->l == nullptr && a->u) a = a->u;
        while (b->d == nullptr && b->r) b = b->r;
        if (a == b) {
            empty_squares.insert({points[i], Point{a->x,a->y}});
        }
    }

    Node* bottom_left = coord_to_node(0, 0);
    Node* top_right = coord_to_node(L, L);

    bool ret = free_square(bottom_left, top_right);

    if (!ret) {
        return {};
    } else {
        reverse(begin(moves), end(moves));
        return moves;
    }
}
