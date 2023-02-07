# ASPA_simlator
This is simlator for ASPA validation

使い方
・データの取得
  python3 add_data.py
  (AS番号を0から1000個づつ１つのファイルにして出力してくれる)
  
・データの整形
  python3 find_rir.py > rir_asn
  python3 make_graph.py < rir_asn > ripe_graph.yaml
  python3 cpp_siml_maker.py > in
  
・シミュレーション
  python3 attack.py
  
各所ファイル名やAS番号などがハードコーディングされているため、必要に応じて変更してください.
