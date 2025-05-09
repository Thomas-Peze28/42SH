FROM aflplusplus/aflplusplus

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    zip \
    tmux

ENV TERM=xterm-256color
ENV CC=afl-clang-fast

COPY src/epitfl.sh /bin/epitfl
COPY src/entrypoint.sh /entrypoint.sh

RUN chmod +x /bin/epitfl /entrypoint.sh

WORKDIR /doit

ENTRYPOINT ["/entrypoint.sh"]
