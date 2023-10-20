from ubuntu:latest

run apt update

# install tools
run apt install -y git
run git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset - %s %C(yellow)%d%Creset %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"

run apt install -y bash-completion
run apt install -y htop
run apt install -y less
run apt install -y tmux
run apt install -y tree
run apt install -y vim
run apt install -y wget

# dot files
workdir /root
run git clone https://github.com/skeggib/dotfiles.git
run rm -f .bashrc .inputrc .vimrc .gdbinit .gitconfig .tmux.conf .tmux.conf.local
run ln -s dotfiles/.bashrc .bashrc
run ln -s dotfiles/.gdbinit .gdbinit
run ln -s dotfiles/.gitconfig .gitconfig
run ln -s dotfiles/.inputrc .inputrc
run ln -s dotfiles/.tmux.conf .tmux.conf
run ln -s dotfiles/.tmux.conf.local .tmux.conf.local
run ln -s dotfiles/.vimrc .vimrc

# c++
run apt install -y g++

# bazel prerequisites
run apt install -y apt-transport-https curl gnupg

# install bazel
run curl -fsSL https://bazel.build/bazel-release.pub.gpg | gpg --dearmor > bazel-archive-keyring.gpg
run mv bazel-archive-keyring.gpg /usr/share/keyrings
run echo "deb [arch=amd64 signed-by=/usr/share/keyrings/bazel-archive-keyring.gpg] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
run apt update
run apt install -y bazel
