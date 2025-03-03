CC=clang
CFLAGS= \
	-I${ROOT_DIR}/../src \
	-I${ROOT_DIR}/../../common/web \
	-I${ROOT_DIR}/../../../include \
	--target=wasm32 \
	-flto \
	-fvisibility=hidden \
	-Ofast
LDFLAGS= \
	-Wl,--allow-undefined \
	-Wl,--no-entry \
	-Wl,--lto-O3 \
	-Wl,-strip-all \
	-Wl,--export-table \
	-Wl,--export=wrapper_new \
	-Wl,--export=wrapper_free \
	-Wl,--export=wrapper_get_ins \
	-Wl,--export=wrapper_get_outs \
	-Wl,--export=wrapper_get_param_values \
	-Wl,--export=wrapper_process \
	-Wl,--export=wrapper_set_parameter \
	-Wl,-z,stack-size=$$((8*1024*1024)) \
	-nostdlib

ROOT_DIR=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
SOURCES= \
	${ROOT_DIR}/../../../src/bw_svf.c \
	${ROOT_DIR}/../src/bw_example_fx_svf.c \
	${ROOT_DIR}/../../common/web/walloc.c \
	${ROOT_DIR}/../../common/web/wrapper.c

all: build/web/module.wasm build/web/index.html build/web/config.js build/web/processor.js build/web/cert.pem build/web/key.pem

build/web/module.wasm: build/web ${SOURCES}
	${CC} ${SOURCES} ${CFLAGS} ${LDFLAGS} -o $@

build/web/index.html: build/web ${ROOT_DIR}/index.html
	cp ${ROOT_DIR}/index.html $@

build/web/processor.js: build/web ${ROOT_DIR}/config.js ${ROOT_DIR}/../../common/web/processor.js
	cat ${ROOT_DIR}/config.js ${ROOT_DIR}/../../common/web//processor.js > $@

build/web/config.js: build/web ${ROOT_DIR}/config.js
	cp ${ROOT_DIR}/config.js $@

build/web/key.pem: build/web/cert.pem

build/web/cert.pem: build/web
	yes "" | openssl req -x509 -newkey rsa:2048 -keyout build/web/key.pem -out build/web/cert.pem -days 365 -nodes 2>/dev/null

build/web:
	mkdir -p build/web

clean:
	rm -fr build/web
