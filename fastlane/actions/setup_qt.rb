# frozen_string_literal: true

module Fastlane
  module Actions
    class SetupQtAction < Action
      def self.run(params)
        UI.message "Setting up Qt for: #{params[:platform]}"
        unless %w[ios_qt5 ios_qt6].include? params[:platform]
          UI.error 'Unsupported platform'
          return
        end

        qt_path = if params[:platform].include? 'qt5'
                    ENV['Qt5_Dir']
                  else
                    ENV['Qt6_Dir']
                  end

        UI.message "Qt path: #{qt_path}"

        # Remove unneeded stuff
        case params[:platform]
        when 'ios_qt6'
          to_remove = []
        when 'ios_qt5'
          to_remove = [
            'lib/libqmapboxgl.a',
            'lib/libqmapboxgl_debug.a',
            'lib/cmake/Qt5Location/Qt5Location_GeoServiceProviderFactoryEsri.cmake',
            'lib/cmake/Qt5Location/Qt5Location_GeoServiceProviderFactoryEsri_Import.cpp',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryEsri.cmake',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryEsri_Import.cpp',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryItemsOverlay.cmake',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryItemsOverlay_Import.cpp',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryMapbox.cmake',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryMapbox_Import.cpp',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryMapboxGL.cmake',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryMapboxGL_Import.cpp',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryNokia.cmake',
            'lib/cmake/Qt5Location/Qt5Location_QGeoServiceProviderFactoryNokia_Import.cpp',
            'mkspecs/modules/qt_plugin_qtgeoservices_esri.pri',
            'mkspecs/modules/qt_plugin_qtgeoservices_itemsoverlay.pri',
            'mkspecs/modules/qt_plugin_qtgeoservices_mapbox.pri',
            'mkspecs/modules/qt_plugin_qtgeoservices_mapboxgl.pri',
            'mkspecs/modules/qt_plugin_qtgeoservices_nokia.pri',
            'plugins/geoservices/libqtgeoservices_esri.a',
            'plugins/geoservices/libqtgeoservices_esri.prl',
            'plugins/geoservices/libqtgeoservices_esri_debug.a',
            'plugins/geoservices/libqtgeoservices_esri_debug.prl',
            'plugins/geoservices/libqtgeoservices_itemsoverlay.a',
            'plugins/geoservices/libqtgeoservices_itemsoverlay.prl',
            'plugins/geoservices/libqtgeoservices_itemsoverlay_debug.a',
            'plugins/geoservices/libqtgeoservices_itemsoverlay_debug.prl',
            'plugins/geoservices/libqtgeoservices_mapbox.a',
            'plugins/geoservices/libqtgeoservices_mapbox.prl',
            'plugins/geoservices/libqtgeoservices_mapbox_debug.a',
            'plugins/geoservices/libqtgeoservices_mapbox_debug.prl',
            'plugins/geoservices/libqtgeoservices_mapboxgl.a',
            'plugins/geoservices/libqtgeoservices_mapboxgl.prl',
            'plugins/geoservices/libqtgeoservices_mapboxgl_debug.a',
            'plugins/geoservices/libqtgeoservices_mapboxgl_debug.prl',
            'plugins/geoservices/libqtgeoservices_nokia.a',
            'plugins/geoservices/libqtgeoservices_nokia.prl',
            'plugins/geoservices/libqtgeoservices_nokia_debug.a',
            'plugins/geoservices/libqtgeoservices_nokia_debug.prl',
            'qml/QtQuick/Controls.2/Fusion',
            'qml/QtQuick/Controls.2/Imagine',
            'qml/QtQuick/Controls.2/Material',
            'qml/QtQuick/Controls.2/Universal',
            'qml/QtQuick/Controls.2/designer'
          ]
        end

        to_remove.each do |path_string|
          path = Pathname.new(qt_path) + path_string
          if path.exist?
            UI.message "Removing #{path}"
            path.rmtree
          end
        end
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Setup Qt for Vremenar'
      end

      def self.details
        'This action removes unneeded data from Qt installation for easier deployment.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :platform,
                                       env_name: 'FL_SETUP_QT_PLATFORM',
                                       description: 'Platform',
                                       is_string: true,
                                       default_value: 'ios_qt5')
        ]
      end

      def self.output
        []
      end

      def self.authors
        ['@ntadej']
      end

      def self.is_supported?(platform)
        platform == :ios
      end
    end
  end
end
