.PHONY: all build clean test

IMAGENAME=gomalishjl

all: build

build:
	-rm -rf .venv Manifest.toml
	docker build -t ${IMAGENAME} .
	docker-compose build
	docker-compose run --rm julia julia --project=/work -e 'using Pkg; Pkg.instantiate()'

test:
	docker-compose run --rm julia julia -e 'using Pkg; Pkg.build(); Pkg.test()'

clean:
	rm -f Manifest.toml
	${MAKE} -C deps clean
	docker-compose down
