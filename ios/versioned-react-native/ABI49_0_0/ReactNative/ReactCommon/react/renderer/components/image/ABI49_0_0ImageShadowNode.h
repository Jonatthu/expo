/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <ABI49_0_0React/ABI49_0_0renderer/components/image/ImageEventEmitter.h>
#include <ABI49_0_0React/ABI49_0_0renderer/components/image/ImageProps.h>
#include <ABI49_0_0React/ABI49_0_0renderer/components/image/ImageState.h>
#include <ABI49_0_0React/ABI49_0_0renderer/components/view/ConcreteViewShadowNode.h>
#include <ABI49_0_0React/renderer/imagemanager/ABI49_0_0ImageManager.h>
#include <ABI49_0_0React/renderer/imagemanager/ABI49_0_0primitives.h>

namespace ABI49_0_0facebook {
namespace ABI49_0_0React {

extern const char ImageComponentName[];

/*
 * `ShadowNode` for <Image> component.
 */
class ImageShadowNode final : public ConcreteViewShadowNode<
                                  ImageComponentName,
                                  ImageProps,
                                  ImageEventEmitter,
                                  ImageState> {
 public:
  using ConcreteViewShadowNode::ConcreteViewShadowNode;

  static ShadowNodeTraits BaseTraits() {
    auto traits = ConcreteViewShadowNode::BaseTraits();
    traits.set(ShadowNodeTraits::Trait::LeafYogaNode);
    return traits;
  }

  /*
   * Associates a shared `ImageManager` with the node.
   */
  void setImageManager(const SharedImageManager &imageManager);

  static ImageState initialStateData(
      ShadowNodeFragment const &fragment,
      ShadowNodeFamilyFragment const &familyFragment,
      ComponentDescriptor const &componentDescriptor) {
    auto imageSource = ImageSource{ImageSource::Type::Invalid};
    return {imageSource, {imageSource, nullptr}, 0};
  }

#pragma mark - LayoutableShadowNode

  void layout(LayoutContext layoutContext) override;

 private:
  ImageSource getImageSource() const;

  SharedImageManager imageManager_;

  void updateStateIfNeeded();
};

} // namespace ABI49_0_0React
} // namespace ABI49_0_0facebook
