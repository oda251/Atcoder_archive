#include "lib.hpp"
// start writing code

int N, M, V;

enum Direction : char {
  UP = 0,
  DOWN,
  LEFT,
  RIGHT,
  NONE,
  DROP,
  PICK,
};
char to_char(Direction dir) {
  switch (dir) {
    case UP: return 'U';
    case DOWN: return 'D';
    case LEFT: return 'L';
    case RIGHT: return 'R';
    case NONE: return 'N';
    case DROP: return 'O';
    case PICK: return 'P';
  }
  return 'N';
}

class Grid {
 private:
  int size;
  array<bitset<32>, 32> row;
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

  const bitset<32>& operator[](int idx) const {
    return row[idx];
  }
};
Grid::Grid() {}
Grid::Grid(Grid &src) {
  this->size = src.size;
  for (int i = 0; i < 32; i++) {
    row[i] = src.row[i];
  }
}
void Grid::init(int size) {
  this->size = size;
  for (int i = 0; i < 32; i++) {
    row[i].reset();
  }
}
void Grid::set(int i, int j, char value) {
  row[i][j] = value;
}
void Grid::set(Point pos, char value) {
  row[pos.y][pos.x] = value;
}
char Grid::get(int i, int j) const {
  return row[i][j];
}
char Grid::get(Point pos) const {
  return row[pos.y][pos.x];
}

typedef unordered_set<Point, Point::Hash, equal_to<Point>> PointSet;
class Data {
 public:
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
  Point rotated(Direction dir) const;
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
  Point parent_pos = parent ? parent->position : position;
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
Point Node::rotated(Direction dir) const {
  Point parent_pos = parent ? parent->position : position;
  Point relative_pos = parent_pos - position;
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
  return parent_pos + rotated_pos;
}

class Arm {
 public:
  Point position;
  Point initPosition;
  vector<Node> nodes;
  vector<Node *> leafNodes;
  vector<Node *> jointNodes;
  int leafSize;
  int maxRadius;
  int takoyakiCount;

  Arm(Data &data);
  Arm(Arm &src);
  char move(Direction dir);
  char canMove(Direction dir) const;
};
Arm::Arm(Data &data) : position(), nodes(V), leafSize(0), takoyakiCount(0) {
  int V = V;
  // 最大半径を設定
  maxRadius = N / 3 * 2;
  // 初期位置
  auto caclInitPosition = [&](int max_radius) {
    max_radius = max_radius - 1;
    int leftUp = 0;
    int rightUp = 0;
    int leftDown = 0;
    int rightDown = 0;
    for (auto& p : data.initialRemainTakoyaki) {
      if (p.x < N / 2) {
        if (p.y < N / 2) {
          leftUp++;
        } else {
          rightUp++;
        }
      } else {
        if (p.y < N / 2) {
          leftDown++;
        } else {
          rightDown++;
        }
      }
    }
    if (leftUp >= rightUp && leftUp >= leftDown && leftUp >= rightDown) {
      return Point(max_radius, 0);
    } else if (rightUp >= leftUp && rightUp >= leftDown && rightUp >= rightDown) {
      return Point(N - max_radius - 1, 0);
    } else if (leftDown >= leftUp && leftDown >= rightUp && leftDown >= rightDown) {
      return Point(max_radius, N - 1);
    } else {
      return Point(N - max_radius - 1, N - 1);
    }
  };
  initPosition = caclInitPosition(maxRadius);
  // 根ノード
  nodes[0].id = 0;
  nodes[0].position = initPosition;
  nodes[0].direction = Direction::NONE;
  // 関節ノード
  for (int i = 1; i < 3; i++) {
    nodes[i].id = i;
    nodes[i].parent = &nodes[0];
    nodes[0].children.push_back(&nodes[i]);
    nodes[i].length = (N / 4) * i;
    nodes[i].position = Point(nodes[i].length, 0);
  }
  // 葉ノード
  for (int i = 0; i < V - 3; i++) {
    int parent = i % 2 == 0 ? 2 : 1;
    int id = i + 3;
    nodes[id].id = id;
    nodes[id].parent = &nodes[parent];
    nodes[parent].children.push_back(&nodes[id]);
    nodes[id].length = i / 2 + 1;
    nodes[id].position = Point(nodes[parent].position.x + 1, nodes[parent].position.y);
    leafSize++;
  }
  for (auto& node : nodes) {
    if (node.isLeaf()) {
      leafNodes.push_back(&node);
    } else {
      jointNodes.push_back(&node);
    }
  }
}
Arm::Arm(Arm &src)
  : position(src.position),
    nodes(src.nodes),
    leafNodes(src.leafNodes),
    jointNodes(src.jointNodes),
    leafSize(src.leafSize),
    maxRadius(src.maxRadius),
    takoyakiCount(src.takoyakiCount) {}
char Arm::move(Direction dir) {
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
  return true;
}
char Arm::canMove(Direction dir) const {
  switch (dir) {
    case Direction::UP:
      if (position.y == 0) return false;
      break;
    case Direction::DOWN:
      if (position.y == N - 1) return false;
      break;
    case Direction::LEFT:
      if (position.x == 0) return false;
      break;
    case Direction::RIGHT:
      if (position.x == N - 1) return false;
      break;
    default:
      break;
  }
  return true;
}

class InGame {
 public:
  int turn;
  Data &data;
  Arm arm;
  vector<string> commandLogs;
  Grid takoyakiGrid;
  PointSet remainDestination;
  PointSet remainTakoyaki;
  int score;
  InGame& operator=(InGame& src);

  InGame(Data &data);
  InGame(InGame &src);
  void output();

  bool isTakoyakiToPick(Point pos);
  void calcScore();
};
InGame::InGame(Data &data)
  : turn(0),
    data(data),
    arm(data),
    commandLogs(),
    takoyakiGrid(data.initialArrangementGrid),
    remainDestination(data.initialRemainDestination),
    remainTakoyaki(data.initialRemainTakoyaki),
    score(-1) {}
InGame::InGame(InGame &src)
  : turn(src.turn),
    data(src.data),
    arm(src.arm),
    commandLogs(src.commandLogs),
    takoyakiGrid(src.takoyakiGrid),
    remainDestination(src.remainDestination),
    remainTakoyaki(src.remainTakoyaki),
    score(src.score) {}
InGame& InGame::operator=(InGame& src) {
  turn = src.turn;
  data = src.data;
  arm = src.arm;
  commandLogs = src.commandLogs;
  takoyakiGrid = src.takoyakiGrid;
  remainDestination = src.remainDestination;
  remainTakoyaki = src.remainTakoyaki;
  score = src.score;
  return *this;
}
void InGame::output() {
  cout << V << '\n';
  for (int i = 1; i < V; i++) {
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
void InGame::calcScore() {
  int score = 0;
  score += M - remainTakoyaki.size();
  score += M - remainDestination.size();
  this->score = score;
}