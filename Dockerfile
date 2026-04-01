from python:trixie as alessa

# hadolint ignore=DL3008
run apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    wget \
    git \
    git-lfs \
    && apt-get autoremove -y \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

workdir /home
copy rom rom
copy requirements.txt requirements.txt
