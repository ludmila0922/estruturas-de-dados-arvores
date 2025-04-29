FROM rockylinux:9

ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN echo "max_parallel_downloads=10" >> /etc/dnf/dnf.conf && \
    echo "fastestmirror=True" >> /etc/dnf/dnf.conf 

RUN dnf install epel-release -y
RUN dnf config-manager --set-enabled crb -y
RUN dnf install git zsh gcc-toolset-14 cmake gdb gtest-devel fira-code-fonts sudo doxygen -y

RUN echo "#!/bin/bash" > /etc/profile.d/enable_venv.sh && \
    echo "source /opt/rh/gcc-toolset-14/enable" >> /etc/profile.d/enable_venv.sh && \
    chmod +x /etc/profile.d/enable_venv.sh

RUN groupadd --gid $USER_GID $USERNAME && \
    useradd -s /usr/bin/zsh --uid $USER_UID --gid $USER_GID -m $USERNAME && \
    echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME && \
    chmod 0440 /etc/sudoers.d/$USERNAME

USER $USERNAME

RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" -s --batch
