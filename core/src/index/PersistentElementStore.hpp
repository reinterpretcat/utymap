#ifndef INDEX_PERSISTENTELEMENTSTORE_HPP_DEFINED
#define INDEX_PERSISTENTELEMENTSTORE_HPP_DEFINED

#include "QuadKey.hpp"
#include "entities/Element.hpp"
#include "index/ElementStore.hpp"

#include <memory>

namespace utymap {
namespace index {

/// Provides API to store elements in persistent store.
class PersistentElementStore final : public ElementStore {
 public:
  PersistentElementStore(const std::string &path,
                         const utymap::index::StringTable &stringTable);

  virtual ~PersistentElementStore();

  void search(const std::string &notTerms,
              const std::string &andTerms,
              const std::string &orTerms,
              const utymap::BoundingBox &bbox,
              const utymap::LodRange &range,
              utymap::entities::ElementVisitor &visitor,
              const utymap::CancellationToken &cancelToken) override;

  void search(const utymap::QuadKey &quadKey,
              utymap::entities::ElementVisitor &visitor,
              const utymap::CancellationToken &cancelToken) override;

  void save(const utymap::entities::Element &element,
            const utymap::QuadKey &quadKey) override;

  bool hasData(const utymap::QuadKey &quadKey) const override;

  void erase(const utymap::QuadKey &quadKey) override;

  void erase(const utymap::BoundingBox &bbox,
             const utymap::LodRange &range) override;

  /// Flushes cached internally data.
  void flush();

 private:
  class PersistentElementStoreImpl;
  std::unique_ptr<PersistentElementStoreImpl> pimpl_;
};

}
}

#endif // INDEX_PERSISTENTELEMENTSTORE_HPP_DEFINED
