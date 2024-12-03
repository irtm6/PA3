FROM alpine AS build
RUN apk add --no-cache git build-base cmake automake autoconf coreutils
WORKDIR /home/optima
RUN git clone https://github.com/irtm6/PA3.git .
RUN [ -f configure ] || autoreconf -i && chmod +x configure && ./configure && make

FROM alpine
RUN apk add --no-cache libstdc++
COPY --from=build /home/optima/funca /usr/local/bin/funca
ENTRYPOINT ["/usr/local/bin/funca"]
