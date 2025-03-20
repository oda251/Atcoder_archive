from operator import attrgetter
 
# class
class Node:
  def __init__(self, node_id):
    self.node_id = node_id
    self.edges = []
  
  def add_edge(self, destination, distance):
    self.edges.append([destination, distance])
 
class Worker:
  def __init__(self, worker_id, ini_v, l_max, n_type, types):
    self.worker_id = worker_id
    self.v = ini_v
    self.l_max = l_max
    self.n_type = n_type
    self.types = types
  
  def move(self, v):
    self.v = v
 
class Job:
  def __init__(self):
    self.validity = [False, None]
    self.completed = False
    self.dependers = []
  
  def set(self, job_id, job_type, n_task, v_job, n_reward, rew_arr, dependees):
    self.job_id = job_id
    self.job_type = job_type
    self.n_task = n_task
    self.v_job = v_job
    self.n_reward = n_reward
    self.rew_arr = rew_arr
    self.dependees = dependees
    self.max_r = [None, 0]
    if dependees == []:
      self.enable(0)
    if rew_arr[0][1] == 0:
      self.ini_no_rew = rew_arr[0][1]
    if rew_arr[-1][1] == 0:
      self.end_no_rew = rew_arr[-1][1]
 
  def add_depender(self, depender):
    self.dependers.append(depender)
 
  def calc_reward_justtime(self, t):
    if t <= self.rew_arr[0][0]:
      return self.rew_arr[0][1]
    elif t >= self.rew_arr[-1][0]:
      return self.rew_arr[-1][1]
    else:
      for i, val in enumerate(rew_arr):
        if val[0] > t:
          former = rew_arr[i - 1]
          latter = val
          break
      return (latter[1] - former[1]) * (t - former[0]) / (latter[0] - former[0]) + former[1]
 
  def calc_reward(self, t1, t2, l_max):
    result = 0
    if not (t2 - t1) * l_max == self.n_task:
      for t in range(t1, t2 - 1):
        rew_at_time = self.calc_reward_justtime(t)
        if rew_at_time <= 0:
          return 0
        result += rew_at_time * l_max
      result += (self.n_task % l_max) * self.calc_reward_justtime(t2 - 1)
    else:
      for t in range(t1, t2):
        rew_at_time = self.calc_reward_justtime(t)
        if rew_at_time <= 0:
          return 0
        result += self.calc_reward_justtime(t) * l_max
    return result
 
  def enable(self, t):
    self.validity = [True, t]
 
  def complete(self, t):
    self.completed = True
    for val in self.dependers:
      jobs[val].dependees.remove(self.job_id)
      if jobs[val].dependees == []:
        jobs[val].enable(t)
 
 
## input
# term
t_max = int(input())
# nodes
nodes_amount, edges_amount = map(int, input().split())
nodes = [None] + [Node(i) for i in range(1, nodes_amount + 1)]
for i in range(edges_amount):
  node1, node2, dist = map(int, input().split())
  nodes[node1].add_edge(node2, dist)
  nodes[node2].add_edge(node1, dist)
# worker
worker_amount = int(input())
workers = [None]
for i in range(1, worker_amount + 1):
  inp = list(map(int, input().split()))
  ini_v = inp[0]
  l_max = inp[1]
  n_type = inp[2]
  types = inp[3:]
  workers.append(Worker(i, ini_v, l_max, n_type, types))
# job
job_amount = int(input())
jobs = [None] + [Job() for i in range(job_amount)]
for i in range(job_amount):
  job_id, job_type, n_task, v_job = map(int, input().split())
 
  inp = list(map(int, input().split()))
  n_reward = inp[0]
  rew_arr = []
  for j, val in enumerate(inp[1:]):
    if j % 2 == 0:
      temp = [val]
    else:
      temp.append(val)
      rew_arr.append(temp)
  
  dep = list(map(int, input().split()))
  if not dep[0] == 0:
    dependees = dep[1:]
    for val in dep[1:]:
      jobs[val].add_depender(job_id)
  else:
    dependees = []
 
  jobs[i+1].set(job_id, job_type, n_task, v_job, n_reward, rew_arr, dependees)
 
# 最短距離リストを生成
def culc_shortest_route(ini):
  node_costs = [None for i in range(nodes_amount+1)]
  ini_routes_list = [[0, ini]]
  while not ini_routes_list == []:
    for i, ini_route in enumerate(ini_routes_list):
      route_list = []
      for val in nodes[ini_route[-1]].edges:
        if not val[0] in ini_route:
          route_list.append([ini_route[0] + val[1]] + ini_route[1:] + [val[0]])
          if node_costs[val[0]] is None or node_costs[val[0]] > ini_route[0] + val[1]:
            node_costs[val[0]] = ini_route[0] + val[1]
        else:
          pass
      ini_routes_list.pop(i)
      ini_routes_list.extend(route_list)
  return node_costs
shortest_routes = [None]
for i in range(1, nodes_amount + 1):
  shortest_routes.append(culc_shortest_route(i))
 
# 処理
result = [[] for i in range(worker_amount)]
workers_sorted = workers[1:]
workers_sorted.sort(key=attrgetter('n_type'))
for w in workers_sorted:
  jobs_w = [elem for elem in jobs[1:] if elem.job_type in w.types]
  t = 0
  while t < t_max:
    # ジョブID、時間当たり平均報酬、終了した時間、移動に要した時間、仕事した時間
    to_do = [None, 0, None, None, None]
    for j in jobs_w:
      if j.completed == True or j.validity[0] == False or j.validity[1] > t:
        pass
      else:
        working_time = - (- j.n_task // w.l_max)
        if j.v_job == w.v:
          start_time = t
          sum_time = working_time
        else:
          start_time = t + shortest_routes[w.v][j.v_job]
          sum_time = shortest_routes[w.v][j.v_job] + working_time
        finished_time = t + sum_time
        if finished_time < t_max:
          reward = j.calc_reward(start_time, start_time + working_time, w.l_max)
          efficiency = reward / sum_time
          if efficiency > to_do[1]:
            to_do = [j.job_id, efficiency, finished_time, start_time - t, working_time]

    # 仕事があるとき
    if not to_do[0] == None:
      # 移動時間
      for i in range(to_do[3]):
        result[w.worker_id - 1].append(f'move {jobs[to_do[0]].v_job}')
      # 仕事してる時間
      check = jobs[to_do[0]].n_task % w.l_max
      if check == 0:
        for i in range(to_do[4]):
          result[w.worker_id - 1].append(f'execute {to_do[0]} {w.l_max}')
      else:
        for i, k in enumerate(range(to_do[4])):
          if i < to_do[4] - 1:
            result[w.worker_id - 1].append(f'execute {to_do[0]} {w.l_max}')
          else:
            result[w.worker_id - 1].append(f'execute {to_do[0]} {check}')
      jobs[to_do[0]].complete(to_do[2] - 1)
      t = to_do[2]
      w.move(jobs[to_do[0]].v_job)
    # 仕事がないとき
    else:
      if t_max - t < 15:
        for i in range(t_max - t):
          result[w.worker_id - 1].append('stay')
        t = t_max
      else:
        for i in range(15):
          result[w.worker_id - 1].append('stay')
        t += 15
 
for arr in result:
  for v in arr:
    print(v)

 
score = input()