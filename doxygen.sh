#!/bin/bash

docker run --rm -v $(pwd):/data -it hrektts/doxygen doxygen
