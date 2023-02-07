#!/bin/bash

num=$1
shift

while [ $# -gt 0 ]
do
  for i in `seq 0 9`
  do
    wget "https://api.bgpview.io/asn/$1"
    if [ $? -eq 0  ]
    then
      break
    fi
  done
  echo -n "$1 " >> "data/detail/detail_dic$num"
  cat $1 >> "data/detail/detail_dic$num"
  echo "" >> "data/detail/detail_dic$num"
  rm $1

  for i in `seq 0 9`
  do
    wget "https://api.bgpview.io/asn/$1/peers"
    if [ $? -eq 0  ]
    then
      break
    fi
  done
  echo -n "$1 " >> "data/peer/peer_dic$num"
  cat peers >> "data/peer/peer_dic$num"
  echo "" >> "data/peer/peer_dic$num"
  rm peers

  for i in `seq 0 9`
  do
    wget "https://api.bgpview.io/asn/$1/downstreams"
    if [ $? -eq 0 ]
    then
      break
    fi
  done
  echo -n "$1 " >> "data/down/down_dic$num"
  cat downstreams >> "data/down/down_dic$num"
  echo "" >> "data/down/down_dic$num"
  rm downstreams

  shift
done

