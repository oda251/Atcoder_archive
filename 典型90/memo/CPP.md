# map
- あるキーが登録されているか判別するとき
  - 未登録のキーでアクセス：
    - 単位元を値とする要素が作成される
    - 実行時間：O(1)
  - find()で探す：
    - 要素は作成されない
    - 実行時間：O({ $keySize })