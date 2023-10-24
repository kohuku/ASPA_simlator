# ASPA_simulator
This is simlator for ASPA validation

## 使い方
### データの取得

  `python3 add_data.py`
  
  (AS番号を0から1000個づつ１つのファイルにして出力してくれる)
  * ditail_dic0にはASN 1〜1000, ditail_dic1にはASN 1001〜2000
  * データの初期フォーマットは、BGPviewから得られるデータの先頭にAS番号を追加したもの
  
### データの整形

  `python3 find_rir.py > rir_asn`
  
  `python3 make_graph.py < rir_asn > ripe_graph.yaml`
  
  `python3 cpp_siml_maker.py > in`
  
### シミュレーション

  - 1つのASから1つのASへの攻撃を行った時の被害AS数を得る場合

  `./sim.out [攻撃ASのAS番号] [ターゲットASのAS番号] [ASPVの導入AS数] < in`
  
  
  
  - ASPVの導入AS数を変化させながら、複数のASから複数のASに攻撃を行って被害AS数を数え、有効性の値を出力する場合

  `python3 attack.py`
  
各所ファイル名やAS番号などがハードコーディングされているため、必要に応じて変更してください.
