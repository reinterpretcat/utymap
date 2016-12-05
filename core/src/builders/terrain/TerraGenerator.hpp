#ifndef BUILDERS_TERRAIN_TERRAGENERATOR_HPP_DEFINED
#define BUILDERS_TERRAIN_TERRAGENERATOR_HPP_DEFINED

#include "builders/BuilderContext.hpp"
#include "builders/terrain/RegionTypes.hpp"
#include "builders/terrain/LineGridSplitter.hpp"

#include <memory>

namespace utymap { namespace builders {

/// Defines behaviour for generating objects on/under/above terrain.
class TerraGenerator
{
public:
    TerraGenerator(const utymap::builders::BuilderContext& context,
                   const utymap::mapcss::Style& style,
                   const ClipperLib::Path& tileRect);

    /// Adds region for given element.
    virtual void addRegion(const std::string& type,
                           const utymap::entities::Element& element,
                           const utymap::mapcss::Style& style,
                           std::shared_ptr<Region> region) = 0;

    /// Generates mesh for given rect.
    virtual void generate() = 0;

    virtual ~TerraGenerator() = default;

protected:
    /// Builds all objects for quadkey organized by layers.
    virtual void buildLayers();

    /// Builds all objects to occupy the space not used by layers
    virtual void buildBackground();

    /// Called to populate mesh with geometry provided by paths
    virtual void addGeometry(ClipperLib::Paths& geometry, const RegionContext& regionContext) = 0;

    /// Restores geometry from clipper format.
    std::vector<utymap::math::Vector2> restoreGeometry(const ClipperLib::Path& geometry) const;

    const utymap::builders::BuilderContext& context_;
    const utymap::mapcss::Style& style_;
    const ClipperLib::Path tileRect_;
    const utymap::math::Rectangle rect_;
    ClipperLib::ClipperEx foregroundClipper_;
    ClipperLib::ClipperEx backgroundClipper_;
    utymap::builders::LineGridSplitter splitter_;
    Layers layers_;

private:
    /// Builds mesh using regions data.
    void buildFromRegions(Regions& regions, const RegionContext& regionContext);

    /// Builds mesh using paths data.
    void buildFromPaths(const ClipperLib::Paths& paths, const RegionContext& regionContext);
};

}}

#endif // BUILDERS_TERRAIN_TERRAGENERATOR_HPP_DEFINED