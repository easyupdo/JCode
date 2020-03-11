#########################################################################
# File Name: build.sh
# Author: JayGuan
# mail:
# Created Time: 五  2/21 17:49:17 2020
#########################################################################
#!/bin/bash

function usages() {
  echo "Help:"
  echo "./x.sh [build_type]"
  echo "--name=          #Docker image name"
  echo "--tag=           #Docker image tag"
  echo "--dfile=         #Dockerfile #input"
  echo "--lfile=         #Logfile #output"
  echo "--version        #Get version"
  echo "--help           #This help"

}
function rel2abs {
  if [ ! -z "$arg" ]; then
    local retval=`cd $arg 2>/dev/null && pwd || exit 1`
    echo $retval
  fi
}
function read_dirname {
  local dir_name=`expr "X$arg" : '[^=]*=\(.*\)'`;
  local retval=`rel2abs $dir_name`
  [ -z $retval ] && echo "Bad option '$arg': no such directory" && exit 1;
  echo $retval

}
function mkimage(){
  echo "Building with:" >> $build_logfile
  echo "images name:$docker_image_name" >> $build_logfile
  echo "images tag:$docker_image_tag" >> $build_logfile
  echo "images used dockerfile:$docker_dockerfile" >> $build_logfile
  docker build -t ${docker_image_name}:${docker_image_tag} -f ${docker_dockerfile} .
}

docker_image_name=lsx/kaldi-5.4
docker_image_tag=kaldi-5.4-cpu-ubuntu16.04-lsx
docker_dockerfile=./Dockerfile.kaldi-cpu
build_logfile=$docker_dockerfile-build.log

if [ $# == 0 ]
then
  echo "Build whit default [Y/N]"
  read what
  if [ $what == "Y" ]
  then
    echo "Building with:"
    echo "images name:$docker_image_name"
    echo "images tag:$docker_image_tag"
    echo "images used dockerfile:$docker_dockerfile"
    #mkimage
  else
    echo "Exit!"
  fi
else

  for arg in $@
  do
    echo $arg
    case "$arg" in
      --help)
        echo "usage"
        usages
        exit 0
        ;;
      --name=*)
        docker_image_name=`expr "X$arg" : '[^=]*=\(.*\)'`
        echo $docker_image_name
        ;;
      --tag=*)
        echo "tag"
        docker_image_tag=`expr "X$arg" : '[^=]*=\(.*\)'`
        echo "Tag:$docker_image_tag"
        ;;
      --dfile=*)
        echo "dfile"
        docker_dockerfile=`expr "X$arg" : '[^=]*=\(.*\)'`
        echo "Dockerfile:$docker_dockerfile"
        ;;
      --lfile=*)
        echo "lfile"
        build_logfile=`expr "X$arg" : '[^=]*=\(.*\)'`
        echo "build_logfile:$build_logfile"
        ;;
      --version)
        echo "version:v0.1"
        ;;
      *) echo "no $arg"
    esac

  done


  #git clone --depth 1 -b 5.4 https://github.com/kaldi-asr/kaldi.git kaldi-5.4

  gitlab_username=
  gitlab_password=
  gitlab_path=
  gitlab_protocol=

  :<<!
  if [ $gitlab_protocol = 'ssh' ]
  then
    git clone --depth=1 -b lsx-ases-2.1 http://${gitlab_username}:${gitlab_password}@${gitlab_path} polly
  else
    echo "HTTP protocol does not support automatic cloing!!! Please git clone it by youself."
  fi
!

# make lsx/kaldi-5.4 image
echo $docker_dockerfile
#mkimage

fi
