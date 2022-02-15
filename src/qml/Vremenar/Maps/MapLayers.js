/*
* Vremenar
* Copyright (C) 2022 Tadej Novak <tadej@tano.si>
*
* This application is bi-licensed under the GNU General Public License
* Version 3 or later as well as Mozilla Public License Version 2.
* Refer to the LICENSE.md file for details.
*
* SPDX-License-Identifier: (GPL-3.0-or-later AND MPL-2.0)
*/

.import Vremenar 1.0 as Common

const beforeLayer = "place_label"

var paramPaints = {}
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
    for (key in paramPaints) {
        let object = paramPaints[key]
        map.removeMapParameter(object)
        object.destroy()
    }
    paramPaints = {}

    for (key in paramLayers) {
        let source = paramLayers[key]
        map.removeMapParameter(source)
        source.destroy()
    }
    paramLayers = {}

    for (key in paramSources) {
        let object = paramSources[key]
        map.removeMapParameter(object)
        object.destroy()
    }
    paramSources = {}
}


function createSource(map, renderingType, url, source)
{
    if (renderingType === Common.Weather.TilesRendering) {
        url += '&bbox={bbox-epsg-3857}'
        return Qt.createQmlObject(`import QtLocation 5.15; DynamicParameter {type: "source"; objectName: "weatherSourceObj${source}"; property var name: "weatherSource${source}"; property var sourceType: "raster"; property var tiles: ["${url}"]; property var tileSize: 512;}`,
                                  map,
                                  "sourceParam")
    } else {
        return Qt.createQmlObject(`import QtLocation 5.15; DynamicParameter {type: "source"; objectName: "weatherSourceObj${source}"; property var name: "weatherSource${source}"; property var sourceType: "image"; property var url: "${url}"; property var coordinates: VMapLayersModel.coordinates;}`,
                                  map,
                                  "sourceParam")
    }
}


function createLayer(map, source)
{
    return Qt.createQmlObject(`import QtLocation 5.15; DynamicParameter {type: "layer"; objectName: "weatherLayerObj${source}"; property var name: "weatherLayer${source}"; property var layerType: "raster"; property var source: "weatherSource${source}"; property var before: "${beforeLayer}"; property var rasterFadeDuration: 0;}`,
                              map,
                              "layerParam")
}


function createPaint(map, visible, source)
{
    let opacity = visible ? 0.75 : 0;
    return Qt.createQmlObject(`import QtLocation 5.15; DynamicParameter {type: "paint";  objectName: "weatherPaintObj${source}"; property var layer: "weatherLayer${source}"; property var rasterOpacity: ${opacity}; property var rasterFadeDuration: 0;}`,
                              map,
                              "paintParam")
}


function createSourceGroup(map, renderingType, url, source)
{
    if (paramSources.hasOwnProperty(source)) {
        return
    }

    let sourceObj = createSource(map, renderingType, url, source)
    paramSources[source] = sourceObj

    let layerObj = createLayer(map, source)
    paramLayers[source] = layerObj

    let paintObj = createPaint(map, false, source)
    paramPaints[source] = paintObj

    map.addMapParameter(sourceObj)
    map.addMapParameter(layerObj)
    map.addMapParameter(paintObj)
}


function hideAllLayers()
{
    for (let param in paramPaints) {
        paramPaints[param].rasterOpacity = 0
    }
}


function addParameters(map, type, renderingType, urlPrevious, urlCurrent, urlNext)
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

    createSourceGroup(map, renderingType, urlPrevious, labelPrevious)
    createSourceGroup(map, renderingType, urlCurrent, labelCurrent)
    createSourceGroup(map, renderingType, urlNext, labelNext)

    hideAllLayers()
    paramPaints[labelCurrent].rasterOpacity = 0.75
}
