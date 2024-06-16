from operator import attrgetter
 
# class
class Node:
  def __init__(self, node_id):
    self.node_id = node_id
    self.edges = []
    self.jobs = set()
    self.shortest_h = dict()
    self.shortest = {self.node_id: 0}
  
  def set_shortest_h(self, dest, dist):
    self.shortest_h[dest] = dist
  
  def set_shortest(self, dest, dist):
    self.shortest[dest] = dist
  
  def add_edge(self, destination, distance):
    self.edges.append((destination, distance))

  def add_job(self, job_id):
    self.jobs.add(job_id)

class AstarParams:
  def __init__(self, g=0, h=0, f=0):
    self.g = g
    self.h = h
    self.f = f
    self.closed = False

  def open(self):
    self.closed = False

  def close(self):
    self.closed = True

  def set_params(self, g=0, h=0, f=0):
    self.g = g
    self.h = h
    self.f = f
 
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
    self.validity = [False, float('inf')]
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
    if not dependees:
      self.validity = [True, 0]
    self.rew_timeline = [self.calc_reward_at_time(t) for t in range(1, t_max + 1)]
    self.max_rew = max(self.rew_timeline)
 
  def add_depender(self, depender):
    self.dependers.append(depender)
 
  def calc_reward_at_time(self, t):
    if t <= self.rew_arr[0][0]:
      return self.rew_arr[0][1]
    elif t >= self.rew_arr[-1][0]:
      return self.rew_arr[-1][1]
    else:
      for i, val in enumerate(self.rew_arr):
        if val[0] > t:
          former = self.rew_arr[i - 1]
          latter = val
          break
      return (latter[1] - former[1]) * (t - former[0]) / (latter[0] - former[0]) + former[1]

  def calc_reward(self, t1, t2, l_max):
    if 0 in self.rew_timeline[t1 - 1:t2 - 1]:
      return 0
    check = self.n_task % l_max
    if check == 0:
      result = sum(self.rew_timeline[t1 - 1:t2 - 1]) * l_max
    else:
      result = sum(self.rew_timeline[t1 - 1:t2 - 2]) * l_max
      result += self.rew_timeline[t2 - 2] * check
    # 時給が最大より一定低い場合に避けるようにする
    if max(self.rew_timeline[t1 - 1:t2 - 1]) < self.max_rew * 0.7:
      result /= 2.5
    elif max(self.rew_timeline[t1 - 1:t2 - 1]) < self.max_rew * 0.8:
      result /= 1.5
    return result

  def complete(self, fin_t):
    self.completed = True
    for v in self.dependers:
      jobs[v].rm_dependee(self.job_id, fin_t)

  def rm_dependee(self, j_id, fin_t):
    self.dependees.remove(j_id)
    if self.validity[1] < fin_t:
      self.validity[1] = fin_t
    if not self.dependees:
      self.validity[0] = True

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
  types = set(inp[3:])
  workers.append(Worker(i, ini_v, l_max, n_type, types))
# job
job_amount = int(input())
jobs = [None] + [Job() for i in range(job_amount)]
for i in range(job_amount):
  job_id, job_type, n_task, v_job = map(int, input().split())
  nodes[v_job].add_job(job_id)
 
  inp = list(map(int, input().split()))
  n_reward = inp[0]
  rew_arr = []
  j = True
  for val in inp[1:]:
    if j:
      rew_t = val
      j = False
    else:
      rew_arr.append((rew_t, val))
      j = True

  inp = list(map(int, input().split()))
  dependees = set(inp[1:])
  for val in inp[1:]:
    jobs[val].add_depender(job_id)
 
  jobs[i+1].set(job_id, job_type, n_task, v_job, n_reward, rew_arr, dependees)

#### エッジが多くないとき ###############################################
if edges_amount < 2000:
  # 最短距離リストを生成
  def calc_shortest_routes():
    for s in range(1, nodes_amount + 1):
      new = {s}
      open_l = {s:True}
      for v in range(s + 1, nodes_amount + 1):
        nodes[s].set_shortest(v, float('inf'))
        open_l[v] = True
      for v in range(1, s + 1):
        open_l[v] = False
        for dest, dist in nodes[v].edges:
          if dest <= s:
            continue
          temp = nodes[s].shortest[v] + dist
          if nodes[s].shortest[dest] > temp:
            nodes[s].shortest[dest] = temp
            nodes[dest].shortest[s] = temp
            open_l[dest] = True
            new.add(dest)
      while new:
        current = next(iter(new))
        for v in new:
          if nodes[s].shortest[v] < nodes[s].shortest[current]:
            current = v
        new.remove(current)
        if open_l[current] == False:
          continue
        open_l[current] = False
        for dest, dist in nodes[current].edges:
          temp = nodes[s].shortest[current] + dist
          if open_l[dest] == False:
            if nodes[s].shortest[dest] > temp:
              nodes[s].shortest[dest] = temp
              nodes[dest].shortest[s] = temp
              open_l[dest] = True
              new.add(dest)
          else:
            if nodes[s].shortest[dest] > temp:
              nodes[s].shortest[dest] = temp
              nodes[dest].shortest[s] = temp
              new.add(dest)
  
  calc_shortest_routes()
  
  # 処理
  result = [[] for i in range(worker_amount)]
  workers_sorted = workers[1:]
  workers_sorted.sort(key=attrgetter('n_type'))
  t = 1
  w_status = [0 for i in range(worker_amount)]
  while t <= t_max:
    for w in workers_sorted:
      if w_status[w.worker_id - 1] >= t:
        continue
      jobs_w = [elem for elem in jobs[1:] if elem.job_type in w.types and elem.completed == False and elem.validity[1] < t]
      # ジョブID、時間当たり平均報酬、終了した時間、移動に要した時間、仕事した時間
      to_do = [None, 0, None, None, None, None]
      if jobs_w:
        for j in jobs_w:
          cost = nodes[w.v].shortest[j.v_job]
          working_time = - (- j.n_task // w.l_max)
          start_time = t + cost
          sum_time = working_time + cost
          finished_time = t + sum_time
          if finished_time - 1 < t_max:
            reward = j.calc_reward(start_time, finished_time, w.l_max)
            coefficient = 1.04 ** sum_time
            efficiency = reward / sum_time / coefficient / (cost / 40 + 1)
            if efficiency > to_do[1]:
              to_stay = 0
              to_do = [j.job_id, efficiency, finished_time + to_stay, cost, working_time, to_stay]
            for i in range(1, 9):
              if finished_time + i - 1 < t_max:
                coefficient *= 1.04
                reward = j.calc_reward(start_time + i, finished_time + i, w.l_max)
                efficiency = reward / (sum_time + i) / coefficient / (cost / 40 + 1)
                if efficiency > to_do[1]:
                  to_stay = i
                  to_do = [j.job_id, efficiency, finished_time + to_stay, cost, working_time, to_stay]
              else:
                break

      # 仕事があるとき
      if to_do[0]:
        # 移動時間
        for _ in range(to_do[3]):
          result[w.worker_id - 1].append(f'move {jobs[to_do[0]].v_job}')
        # 待機時間
        for _ in range(to_do[5]):
          result[w.worker_id - 1].append('stay')
        # 仕事してる時間
        check = jobs[to_do[0]].n_task % w.l_max
        if check == 0:
          for _ in range(to_do[4]):
            result[w.worker_id - 1].append(f'execute {to_do[0]} {w.l_max}')
        else:
          for i, k in enumerate(range(to_do[4])):
            if i < to_do[4] - 1:
              result[w.worker_id - 1].append(f'execute {to_do[0]} {w.l_max}')
            else:
              result[w.worker_id - 1].append(f'execute {to_do[0]} {check}')
        jobs[to_do[0]].complete(to_do[2] - 1)
        w.move(jobs[to_do[0]].v_job)
        w_status[w.worker_id - 1] = to_do[2] - 1
      # 仕事がないとき
      else:
        param = 1
        if t_max - w_status[w.worker_id - 1] < param:
          for _ in range(t_max - t + 1):
            result[w.worker_id - 1].append('stay')
          w_status[w.worker_id - 1] = t_max + 1
        else:
          for _ in range(param):
            result[w.worker_id - 1].append('stay')
          w_status[w.worker_id - 1] += param
    t += 1

#### エッジが多いとき ########################################
else:
  # ジョブ探索範囲
  times, selected = 17, 80
  if edges_amount > 2400:
    times = 16
  elif edges_amount > 2800:
    times, selected = 15, 40

  # 一定範囲内のジョブを探索
  def get_jobs(t, w_types, s):
    job_list = []
    check_v_list = [s]
    checked = set()
    for i in range(1, times):
      next_v_list = []
      for check_v in check_v_list:
        for e, cost in nodes[check_v].edges:
          if e in checked:
            continue
          # ヒューリスティック関数パラメータにキャッシュ
          if not e in nodes[s].shortest_h.keys():
            nodes[s].shortest_h[e] = i
            nodes[e].shortest_h[s] = i
          for job_id in nodes[e].jobs:
            j = jobs[job_id]
            if j.job_type in w_types and j.completed == False and j.validity[0] == True and j.validity[1] < t:
              job_list.append(j.job_id)
              if len(job_list) > selected:
                return job_list
          next_v_list.append(e)
          checked.add(e)
      if next_v_list:
        check_v_list = next_v_list
      else:
        break
    return job_list

  # ヒューリスティック関数(特定の２頂点間の重み抜き最短距離を求める)
  def breadth_f_serch(s, g):
    if g in nodes[s].shortest_h.keys():
      return nodes[s].shortest_h[g]
    check_v_list = [s]
    checked = set()
    cost = 1
    while True:
      next_check_v_list = []
      for check_v in check_v_list:
        for e, no_use in nodes[check_v].edges:
          if e in checked:
            continue
          if not e in nodes[s].shortest_h.keys():
            nodes[s].shortest_h[e] = cost
            nodes[e].shortest_h[s] = cost
          if e == g:
            return cost
          next_check_v_list.append(e)
          checked.add(e)
      check_v_list = next_check_v_list
      cost += 1

  # A*探索
  def calc_cost(s, g):
    try:
      return nodes[s].shortest[g]
    except KeyError:
      # AstarParams(g, h, f)
      astar_params = dict([(s, AstarParams())])
      open_l = {s}
      while open_l:
        current = next(iter(open_l))
        # OPENリスト内でコスト最小のノードを取得
        for v in open_l:
          if astar_params[v].f < astar_params[current].f:
            current = v
        open_l.remove(current)
        # 取得したノードがCLOSEならスキップ
        if astar_params[current].closed:
          continue
        # 現在のノード = ゴールの場合の終了処理
        if current == g:
          nodes[s].set_shortest(g, astar_params[current].g)
          nodes[g].set_shortest(s, astar_params[current].g)
          return astar_params[current].g
        # 現在のノードをCLOSEする
        astar_params[current].close()
        # 現在のノードから枝を伸ばす
        for dest, dist in nodes[current].edges:
          # destのhを計算 (hはノードに対して固定なので既知ならばキャッシュから取得)
          try:
            dest_h = astar_params[dest].h
          except KeyError:
            dest_h = breadth_f_serch(dest, g)
          # destのfを計算
          dest_f = astar_params[current].g + dist + dest_h
          try:
            # destがCLOSEの場合
            if astar_params[dest].closed:
              if dest_f < astar_params[dest].f:
                dest_g = dest_f - dest_h
                astar_params[dest].set_params(dest_g, dest_h, dest_f)
                astar_params[dest].open()
                open_l.add(dest)
            # destがOPENの場合
            else:
              if dest_f < astar_params[dest].f:
                dest_g = dest_f - dest_h
                astar_params[dest].set_params(dest_g, dest_h, dest_f)
          # destが未知の場合
          except KeyError:
            dest_g = dest_f - dest_h
            astar_params[dest] = AstarParams(dest_g, dest_h, dest_f)
            open_l.add(dest)

  result = [[] for i in range(worker_amount)]
  workers_sorted = workers[1:]
  workers_sorted.sort(key=attrgetter('n_type'))
  t = 1
  w_status = [0 for i in range(worker_amount)]
  while t <= t_max:
    for w in workers_sorted:
      if w_status[w.worker_id - 1] >= t:
        continue
      job_list = get_jobs(t, w.types, w.v)
      # ジョブID、時間当たり平均報酬、終了した時間、移動に要した時間、仕事した時間、stayするか
      to_do = [None, 0, None, None, None, None]
      # ジョブの効率を比較
      if job_list:
        for job_id in job_list:
          j = jobs[job_id]
          cost = calc_cost(w.v, j.v_job)
          working_time = - (- j.n_task // w.l_max)
          start_time = t + cost
          sum_time = working_time + cost
          finished_time = t + sum_time
          if finished_time - 1 < t_max:
            reward = j.calc_reward(start_time, finished_time, w.l_max)
            coefficient = 1.01 ** sum_time
            efficiency = reward / sum_time / coefficient / (cost / 40 + 1)
            if efficiency > to_do[1]:
              to_stay = 0
              to_do = [j.job_id, efficiency, finished_time + to_stay, cost, working_time, to_stay]
            for i in range(1, 9):
              if finished_time + i - 1 < t_max:
                coefficient *= 1.01
                reward = j.calc_reward(start_time + i, finished_time + i, w.l_max)
                efficiency = reward / (sum_time + i) / coefficient / (cost / 40 + 1)
                if efficiency > to_do[1]:
                  to_stay = i
                  to_do = [j.job_id, efficiency, finished_time + to_stay, cost, working_time, to_stay]
              else:
                break

      # 仕事があるとき
      if to_do[0]:
        # 移動時間
        for _ in range(to_do[3]):
          result[w.worker_id - 1].append(f'move {jobs[to_do[0]].v_job}')
        # 待機時間
        for _ in range(to_do[5]):
          result[w.worker_id - 1].append('stay')
        # 仕事してる時間
        check = jobs[to_do[0]].n_task % w.l_max
        if check == 0:
          for _ in range(to_do[4]):
            result[w.worker_id - 1].append(f'execute {to_do[0]} {w.l_max}')
        else:
          for i, k in enumerate(range(to_do[4])):
            if i < to_do[4] - 1:
              result[w.worker_id - 1].append(f'execute {to_do[0]} {w.l_max}')
            else:
              result[w.worker_id - 1].append(f'execute {to_do[0]} {check}')
        jobs[to_do[0]].complete(to_do[2] - 1)
        w.move(jobs[to_do[0]].v_job)
        w_status[w.worker_id - 1] = to_do[2] - 1
      # 仕事がないとき
      else:
        param = 1
        if t_max - w_status[w.worker_id - 1] < param:
          for _ in range(t_max - t + 1):
            result[w.worker_id - 1].append('stay')
          w_status[w.worker_id - 1] = t_max + 1
        else:
          for _ in range(param):
            result[w.worker_id - 1].append('stay')
          w_status[w.worker_id - 1] += param
    t += 1
 
# 出力
for i in range(t_max):
  for j in range(worker_amount):
      print(result[j][i])
  
# 終わり
score = input()