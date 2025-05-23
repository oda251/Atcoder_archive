#include "lib.hpp"
// start writing code

enum Direction : char {
  UP = 'U',
  DOWN = 'D',
  LEFT = 'L',
  RIGHT = 'R',
  NONE = '.',
  DROP = 'D',
  PICK = 'P',
};

class Grid {
 private:
  int size;
  array<bitset<32>, 32> row;
  array<bitset<32>, 32> col;
 public:
  enum Direction {
    X,
    Y,
  };
  Grid();
  Grid(Grid &grid);
  void init(int size);
  void set(int i, int j, char value);
  void set(Point pos, char value);
  char get(int i, int j) const;
  char get(Point pos) const;
  int  count(int idx, Direction dir) const;
  int  countStartSide(Point pos, Direction dir) const;
  int  countEndSide(Point pos, Direction dir) const;

  const bitset<32>& operator[](int idx) const {
    return row[idx];
  }
};
Grid::Grid() {}
Grid::Grid(Grid &src) {
  this->size = src.size;
  for (int i = 0; i < 32; i++) {
    row[i] = src.row[i];
    col[i] = src.col[i];
  }
}
void Grid::init(int size) {
  this->size = size;
  for (int i = 0; i < 32; i++) {
    row[i].reset();
    col[i].reset();
  }
}
void Grid::set(int i, int j, char value) {
  row[i][j] = value;
  col[j][i] = value;
}
void Grid::set(Point pos, char value) {
  row[pos.y][pos.x] = value;
  col[pos.x][pos.y] = value;
}
char Grid::get(int i, int j) const {
  return row[i][j];
}
char Grid::get(Point pos) const {
  return row[pos.y][pos.x];
}
int Grid::count(int idx, Direction dir) const {
  return (dir == X ? row[idx].count() : col[idx].count());
}
int Grid::countStartSide(Point pos, Direction dir) const {
  int count = 0;
  if (dir == X) {
    for (int i = 0; i < pos.x; i++) {
      count += row[pos.y][i];
    }
  } else {
    for (int i = 0; i < pos.y; i++) {
      count += col[pos.x][i];
    }
  }
  return count;
}
int Grid::countEndSide(Point pos, Direction dir) const {
  int count = 0;
  if (dir == X) {
    for (int i = pos.x + 1; i < size; i++) {
      count += row[pos.y][i];
    }
  } else {
    for (int i = pos.y + 1; i < size; i++) {
      count += col[pos.x][i];
    }
  }
  return count;
}

typedef unordered_set<Point, Point::Hash, equal_to<Point>> PointSet;
class Data {
 public:
  int N; // size of grid
  int M; // amount of takoyaki
  int V; // node size of arm
  Grid initialArrangementGrid; // initial arrangement of takoyaki
  Grid destinationsGrid; // distinations of takoyaki
  PointSet initialRemainTakoyaki;
  PointSet initialRemainDestination;

  Data();
};
Data::Data() {
  cin >> N >> M >> V;
  initialArrangementGrid.init(N);
  destinationsGrid.init(N);
  for (int i=0; i<N; i++) {
    string line;
    cin >> line;
    for (int j=0; j<N; j++) {
      if (line[j] == '1') {
        initialArrangementGrid.set(i, j, true);
        initialRemainTakoyaki.insert(Point(j, i));
      }
    }
  }
  for (int i=0; i<N; i++) {
    string line;
    cin >> line;
    for (int j=0; j<N; j++) {
      if (line[j] == '1') {
        destinationsGrid.set(i, j, true);
        if (!initialArrangementGrid.get(i, j)) {
          initialRemainDestination.insert(Point(j, i));
        } else {
          initialRemainTakoyaki.erase(Point(j, i));
        }
      }
    }
  }
}

class Node {
 public:
  int id;
  Point position;
  Node* parent;
  int length;
  vector<Node*> children;
  Direction direction;
  bool hasTakoyaki;

  Node();
  Node(Node& src);
  Node& operator=(Node& src);
  bool isLeaf() const;
  void setChild(Node* child);
  void rotate(Direction dir);
  void pickTakoyaki(Grid& grid);
  void putTakoyaki(Grid& grid);
};
Node::Node() : parent(nullptr), length(0), children(), direction(RIGHT), hasTakoyaki(false) {}
Node::Node(Node& src) : id(src.id), position(src.position), parent(src.parent), length(src.length), children(src.children), direction(src.direction), hasTakoyaki(src.hasTakoyaki) {}
Node& Node::operator=(Node& src) {
  id = src.id;
  position = src.position;
  parent = src.parent;
  length = src.length;
  children = src.children;
  direction = src.direction;
  return *this;
}
bool Node::isLeaf() const {
  return children.empty();
}
void Node::setChild(Node* child) {
  children.push_back(child);
}
void Node::rotate(Direction dir) {
  Point parent_pos = parent->position;
  // 対象ノードを収集
  vector<Node*> targets;
  function<void(Node*)> collect = [&](Node *node) {
    targets.push_back(node);
    for (Node* child : node->children) {
      collect(child);
    }
  };
  collect(this);
  for (Node* target : targets) {
    // 位置を回転
    Point relative_pos = parent_pos - target->position;
    Point rotated_pos;
    switch (dir) {
      case Direction::LEFT:
        // 反時計回り
        rotated_pos = Point(-relative_pos.y, relative_pos.x);
        break;
      case Direction::RIGHT:
        // 時計回り
        rotated_pos = Point(relative_pos.y, -relative_pos.x);
        break;
      default:
        break;
    }
    target->position = parent_pos + rotated_pos;
  }
}
void Node::pickTakoyaki(Grid& grid) {
  grid.set(position, false);
  hasTakoyaki = true;
}
void Node::putTakoyaki(Grid& grid) {
  grid.set(position, true);
  hasTakoyaki = false;
}

class Arm {
 public:
  Point position;
  Point initPosition;
  vector<Node> nodes;
  int leafSize;
  int maxRadius;

  Arm(Data &data);
  void move(Direction dir);
};
Arm::Arm(Data &data) : position(), nodes(data.V), leafSize(0) {
  int V = data.V;
  // 最大半径を設定
  maxRadius = (data.N / 3) * 2;
  // 初期位置
  auto caclInitPosition = [&](int max_radius) {
    max_radius = max_radius - 1;
    int leftUp = 0;
    int rightUp = 0;
    int leftDown = 0;
    int rightDown = 0;
    for (auto& p : data.initialRemainTakoyaki) {
      if (p.x < data.N / 2) {
        if (p.y < data.N / 2) {
          leftUp++;
        } else {
          rightUp++;
        }
      } else {
        if (p.y < data.N / 2) {
          leftDown++;
        } else {
          rightDown++;
        }
      }
    }
    if (leftUp >= rightUp && leftUp >= leftDown && leftUp >= rightDown) {
      return Point(max_radius, 0);
    } else if (rightUp >= leftUp && rightUp >= leftDown && rightUp >= rightDown) {
      return Point(data.N - max_radius - 1, 0);
    } else if (leftDown >= leftUp && leftDown >= rightUp && leftDown >= rightDown) {
      return Point(max_radius, data.N - 1);
    } else {
      return Point(data.N - max_radius - 1, data.N - 1);
    }
  };
  initPosition = caclInitPosition(maxRadius);
  // 根ノード
  nodes[0].id = 0;
  nodes[0].position = initPosition;
  nodes[0].direction = Direction::NONE;
  // 以降
  for (int i = 1; i < V; i += 5) {
    // 関節ノード
    {
      // idを設定
      nodes[i].id = i;
      // 親子関係を設定
      nodes[i].parent = &nodes[0];
      nodes[0].children.push_back(&nodes[i]);
      // 長さを設定
      const int length = (i == 1 ? 1 : i == 6 ? 3 : 2);
      nodes[i].length = length;
      // 位置を設定
      nodes[i].position = Point(length, 0);
      // 葉ノードの数をカウント
      if (i == V - 1) {
        leafSize++;
      }
    }
    // 葉ノード
    if (i != 11) {
      for (int j = 1; j < 5 && i + j < V; j++) {
        // idを設定
        nodes[j + i].id = j + i;
        // 親子関係を設定
        nodes[j + i].parent = &nodes[i];
        nodes[i].children.push_back(&nodes[j + i]);
        // 長さを設定
        const int length = (j + 1) / 2;
        nodes[j + i].length = length;
        // 位置を設定
        nodes[j + i].position = Point(nodes[i].position.x + length, nodes[i].position.y);
        // 葉ノードの数をカウント
        leafSize++;
      }
    } else {
        for (int j = 1; j < 5 && i + j < V; j++) {
        // idを設定
        nodes[j + i].id = j + i;
        // 親子関係を設定
        nodes[j + i].parent = &nodes[i];
        nodes[i].children.push_back(&nodes[j + i]);
        // 長さを設定
        const int length = (j <= 2 ? 2 : 1);
        nodes[j + i].length = length;
        // 位置を設定
        nodes[j + i].position = Point(nodes[i].position.x + length, nodes[i].position.y);
        // 葉ノードの数をカウント
        leafSize++;
      }
    }
  }
}
void Arm::move(Direction dir) {
  switch (dir) {
    case Direction::UP:
      position.y -= 1;
      for (Node& node : nodes) {
        node.position.y -= 1;
      }
      break;
    case Direction::DOWN:
      position.y++;
      for (Node& node : nodes) {
        node.position.y++;
      }
      break;
    case Direction::LEFT:
      position.x--;
      for (Node& node : nodes) {
        node.position.x--;
      }
      break;
    case Direction::RIGHT:
      position.x++;
      for (Node& node : nodes) {
        node.position.x++;
      }
      break;
    default:
      break;
  }
}

class InGame {
 public:
  Data &data;
  Arm arm;
  vector<string> commandLogs;
  Grid takoyakiGrid;
  PointSet remainDestination;
  PointSet remainTakoyaki;

  InGame(Data &data);
  void output();

  bool isTakoyakiToPick(Point pos);
};
InGame::InGame(Data &data)
  : data(data),
    arm(data),
    commandLogs(),
    takoyakiGrid(data.initialArrangementGrid),
    remainDestination(data.initialRemainDestination),
    remainTakoyaki(data.initialRemainTakoyaki) {}
void InGame::output() {
  cout << data.V << '\n';
  for (int i = 1; i < data.V; i++) {
    cout << arm.nodes[i].parent->id << ' ' << arm.nodes[i].length << '\n';
  }
  cout << arm.initPosition.y << ' ' << arm.initPosition.x << '\n';
  for (auto &log : commandLogs) {
    cout << log << '\n';
  }
  cout << flush;
}
bool InGame::isTakoyakiToPick(Point pos) {
  return takoyakiGrid.get(pos) && !data.destinationsGrid.get(pos);
}
