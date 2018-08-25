FROM node:8

# RUN pacman -Sy
# ENV TERM='xterm-256color'
# RUN pacman -S --needed --noconfirm \
#   sudo which tar grep sed awk  openssh git
# RUN sed -ie 's/^#\(en_US\.UTF-8 UTF-8\)/\1/' /etc/locale.gen \
#   && locale-gen
# RUN useradd -mU -s /bin/bash docker && echo 'docker:docker' | chpasswd
# # RUN echo "docker ALL=(ALL:ALL) ALL" | (EDITOR="tee -a" visudo)
# # USER docker
# # RUN echo 'alias tmux="tmux -2"' >> ~/.bashrc; \
# #   echo 'set -g default-terminal xterm-256color' >> ~/.tmux.conf
# # RUN touch ~/.bashrc && chmod u+x ~/.bashrc 


WORKDIR /app
COPY . .


# If you have native dependencies, you'll need extra tools
# RUN apk add --no-cache make gcc g++ python
# Ref http://zeromq.org/intro:get-the-software

RUN  npm install

EXPOSE 1884
EXPOSE 1885

CMD ["node", "index.js"]