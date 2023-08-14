# DMLC_CORE=${TVM_ROOT}/3rdparty/dmlc-core
# DLPACK=${TVM_ROOT}/3rdparty/dlpack

CFLAGS = -std=c++17 -O2 -fPIC -Iinclude

LDFLAGS = -ldl -lpthread

ifeq (run,$(firstword $(MAKECMDGOALS)))
  runargs := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(runargs):;@true)
endif

.PHONY: run clean yolo_detection

all: yolo_detection

main.o: main.cpp
	$(CXX) -c $(CFLAGS) -o $@  $^

yolo_detection: main.o
	$(CXX) $(CFLAGS) -o $@ $^ $(LDFLAGS) -ltvm_runtime -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio

clean:
	rm -rf *.o

run:
	./yolo_detection $(filter-out $@,$(MAKECMDGOALS))

%:
	@true

