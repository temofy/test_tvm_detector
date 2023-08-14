python -m tvm.driver.tvmc compile \
--target "llvm" \
--input-shapes "input:[1,3,416,416]" \
--output yolo4-416x416f32-tvm.tar \
pretrained_models/yolo4-416x416f32.onnx
