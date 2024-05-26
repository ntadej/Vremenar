/*
* Vremenar
* Copyright (C) 2024 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

.import Vremenar 1.0 as Common

var paramLayers = {}
var paramSources = {}

var currentType
var currentRenderingType


function hash(string)
{
    var hash = 0, i, chr
    if (string.length === 0) return hash
    for (i = 0; i < string.length; i++) {
        chr   = string.charCodeAt(i)
        hash  = ((hash << 5) - hash) + chr
        hash |= 0 // Convert to 32bit integer
    }
    return hash;
}

function hashString(string)
{
    return hash(string).toString()
}


function reset()
{
    var key
    for (key in paramLayers) {
        let source = paramLayers[key]
        mapStyle.removeParameter(source)
        source.destroy()
    }
    paramLayers = {}

    for (key in paramSources) {
        let object = paramSources[key]
        mapStyle.removeParameter(object)
        object.destroy()
    }
    paramSources = {}
}


function createSource(mapStyle, renderingType, url, source)
{
    if (renderingType === Common.Weather.TilesRendering) {
        if (url.indexOf('{z}') === -1) {
            url += '&bbox={bbox-epsg-3857}'
        }
        return Qt.createQmlObject(`
            import MapLibre 3.0

            SourceParameter {
                styleId: "weatherSource${source}"
                type: "raster"
                property var tiles: ["${url}"]
                property int tileSize: 512
            }
            `,
            mapStyle,
            "sourceParam")
    } else {
        return Qt.createQmlObject(`
            import MapLibre 3.0

            SourceParameter {
                styleId: "weatherSource${source}"
                type: "image"
                property string url: "${url}"
                property var coordinates: VMapLayersModel.coordinates
            }
            `,
            mapStyle,
            "sourceParam")
    }
}


function createLayer(mapStyle, source, visible)
{
    let opacity = visible ? 0.75 : 0;
    return Qt.createQmlObject(`
        import MapLibre 3.0

        LayerParameter {
            styleId: "weatherLayer${source}"
            type: "raster"
            property string source: "weatherSource${source}"

            paint: {
                "raster-fade-duration": 0,
                "raster-opacity": ${opacity}
            }
        }
        `,
        mapStyle,
        "layerParam")
}

function createSourceGroup(mapStyle, renderingType, url, source)
{
    if (paramSources.hasOwnProperty(source)) {
        return
    }

    let sourceObj = createSource(mapStyle, renderingType, url, source)
    paramSources[source] = sourceObj

    let layerObj = createLayer(mapStyle, source)
    paramLayers[source] = layerObj

    mapStyle.addParameter(sourceObj)
    mapStyle.addParameter(layerObj)
}


function hideAllLayers()
{
    for (let param in paramLayers) {
        paramLayers[param].setPaintProperty("raster-opacity", 0)
    }
}


function addParameters(mapStyle, type, renderingType, urlPrevious, urlCurrent, urlNext)
{
    if (currentType !== type || currentRenderingType !== renderingType) {
        reset()
    }

    currentType = type
    currentRenderingType = renderingType

    if (renderingType === Common.Weather.IconsRendering) {
        return
    }

    let labelPrevious = hashString(urlPrevious)
    let labelCurrent = hashString(urlCurrent)
    let labelNext = hashString(urlNext)

    createSourceGroup(mapStyle, renderingType, urlPrevious, labelPrevious)
    createSourceGroup(mapStyle, renderingType, urlCurrent, labelCurrent)
    createSourceGroup(mapStyle, renderingType, urlNext, labelNext)

    hideAllLayers()
    paramLayers[labelCurrent].setPaintProperty("raster-opacity", 0.75)
}
