#ifndef INDEX_ELEMENTSTORE_HPP_DEFINED
#define INDEX_ELEMENTSTORE_HPP_DEFINED

#include "BoundingBox.hpp"
#include "CancellationToken.hpp"
#include "LodRange.hpp"
#include "QuadKey.hpp"
#include "entities/Element.hpp"
#include "entities/ElementVisitor.hpp"
#include "mapcss/StyleProvider.hpp"

namespace utymap {
namespace index {

/// Defines API to store elements.
class ElementStore {
 public:
  explicit ElementStore(const utymap::index::StringTable &stringTable);

  virtual ~ElementStore() = default;

  /// Searches for elements matches given query, bounding box and LOD range
  virtual void search(const std::string &notTerms,
                      const std::string &andTerms,
                      const std::string &orTerms,
                      const utymap::BoundingBox &bbox,
                      const utymap::LodRange &range,
                      utymap::entities::ElementVisitor &visitor,
                      const utymap::CancellationToken &cancelToken) = 0;

  /// Searches for elements for given quadKey
  virtual void search(const utymap::QuadKey &quadKey,
                      utymap::entities::ElementVisitor &visitor,
                      const utymap::CancellationToken &cancelToken) = 0;

  /// Checks whether there is data for given quadkey.
  virtual bool hasData(const utymap::QuadKey &quadKey) const = 0;

  /// Stores element in storage in all affected tiles at given level of details range.
  bool store(const utymap::entities::Element &element,
             const utymap::LodRange &range,
             const utymap::mapcss::StyleProvider &styleProvider);

  /// Stores element in storage only in given quadkey.
  bool store(const utymap::entities::Element &element,
             const utymap::QuadKey &quadKey,
             const utymap::mapcss::StyleProvider &styleProvider);

  /// Stores element in storage only in given bounding box.
  bool store(const utymap::entities::Element &element,
             const utymap::BoundingBox &bbox,
             const utymap::LodRange &range,
             const utymap::mapcss::StyleProvider &styleProvider);

  /// Saves element in given quadkey.
  virtual void save(const utymap::entities::Element &element,
                    const utymap::QuadKey &quadKey) = 0;

  /// Erases all data for given quad key.
  virtual void erase(const utymap::QuadKey &quadKey) = 0;

  /// Erases all data for given bbox and LOD range.
  virtual void erase(const utymap::BoundingBox &bbox,
                     const utymap::LodRange &range) = 0;

 private:
  template<typename Visitor>
  bool store(const utymap::entities::Element &element,
             const utymap::LodRange &range,
             const utymap::mapcss::StyleProvider &styleProvider,
             const Visitor &visitor);

  const std::uint32_t clipKeyId_, skipKeyId_;
};

}
}

#endif // INDEX_ELEMENTSTORE_HPP_DEFINED
