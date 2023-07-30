# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      CREATE_WINDOWS_PACKAGE_OUTPUT_FILE = :CREATE_WINDOWS_PACKAGE_OUTPUT_FILE
    end

    class CreateWindowsPackageAction < Action
      def self.run(params)
        build_path = params[:path] || Actions.lane_context[SharedValues::RUN_QMAKE_PROJECT_PATH]
        build_type = params[:build_type] || Actions.lane_context[SharedValues::RUN_QMAKE_BUILD_TYPE]
        output_path = Actions.lane_context[SharedValues::RUN_QMAKE_OUTPUT_PATH] || build_path
        relative_output_path = Pathname.new(output_path).relative_path_from(Pathname.new(build_path))
        deployment_path = Pathname.new(output_path) / 'deployment'
        relative_build_path = Pathname.new(build_path).relative_path_from(deployment_path)
        project_path = Pathname.new('.').relative_path_from(deployment_path).to_s
        package_path = Pathname.new(output_path) / 'package'

        UI.message "Build path: #{build_path}"
        UI.message "Build type: #{build_type}"
        UI.message "Deployment path: #{deployment_path}"
        UI.message "Package path: #{package_path}"

        FileUtils.mkdir_p deployment_path
        FileUtils.mkdir_p package_path

        prepare_deployment project_path, build_path, deployment_path, 'qt5'
        cleanup_deployment build_type, deployment_path

        output_file_name = ''

        Dir.chdir package_path do
          case build_type
          when 'store'
            program_files = "VFS/ProgramFilesX64/Vremenar"
            FileUtils.mkdir_p program_files
            FileUtils.cp_r "#{relative_output_path}/deployment/.", program_files
            FileUtils.cp_r "#{project_path}/resources/Windows/Assets", "."

            FileUtils.cp_r "#{relative_build_path}/AppxManifest.xml", "."

            Actions.sh "makepri.exe createconfig /cf priconfig.xml /dq en-US /o"
            Actions.sh "makepri.exe new /pr . /cf priconfig.xml /o"
            Actions.sh "makeappx.exe pack /d . /p #{relative_output_path}/Vremenar.msix /o"

            output_file_name = 'Vremenar.msix'
          end
        end

        output_file = "#{output_path}/#{output_file_name}"
        UI.message "Output file: #{output_file}"

        Actions.lane_context[SharedValues::CREATE_WINDOWS_PACKAGE_OUTPUT_FILE] = output_file
      end

      def self.prepare_deployment(project_path, build_path, deployment_path, platform)
        UI.message 'Preparing deployment'

        qt_path = if platform.include? 'qt5'
                    ENV['Qt5_Dir']
                  else
                    ENV['Qt6_Dir']
                  end

        UI.message "Qt path: #{qt_path}"

        relative_path = deployment_path.relative_path_from(Pathname.new(build_path)).to_s

        Dir.chdir build_path do
          FileUtils.cp 'release/Vremenar.exe', "#{relative_path}/Vremenar.exe"

          FileUtils.cp "#{qt_path}/../../Tools/OpenSSL/Win_x64/bin/libcrypto-1_1-x64.dll", "#{relative_path}/libcrypto-1_1-x64.dll"
          FileUtils.cp "#{qt_path}/../../Tools/OpenSSL/Win_x64/bin/libssl-1_1-x64.dll", "#{relative_path}/libssl-1_1-x64.dll"
        end

        Dir.chdir deployment_path do
          command = "windeployqt Vremenar.exe --qmldir \"#{project_path}/src/qml\""
          command += ' --angle --no-opengl-sw --no-qmltooling --no-serialport --no-svg'
          Actions.sh command
        end

        # "setup.iss"
        # "vremenar.ico"
        # "WinSparkle.dll"
      end

      def self.cleanup_deployment(build_type, deployment_path)
        Dir.chdir deployment_path do
          to_remove = [
            'geoservices/qtgeoservices_esri.dll',
            'geoservices/qtgeoservices_itemsoverlay.dll',
            'geoservices/qtgeoservices_mapbox.dll',
            'geoservices/qtgeoservices_nokia.dll',
            'iconengines',
            'imageformats/qgif.dll',
            'imageformats/qicns.dll',
            'imageformats/qico.dll',
            'imageformats/qsvg.dll',
            'imageformats/qtga.dll',
            'imageformats/qtiff.dll',
            'imageformats/qwbmp.dll',
            'imageformats/qwebp.dll',
            'qmltooling',
            'sqldrivers/qsqlodbc.dll',
            'sqldrivers/qsqlpsql.dll',
            'Qt5RemoteObjects.dll',
            'QtQml/RemoteObjects',
            'QtQuick/Controls.2/Fusion',
            'QtQuick/Controls.2/Imagine',
            'QtQuick/Controls.2/Material'
          ]

          case build_type
          when 'store'
            to_remove += [
              'vc_redist.x64.exe'
            ]
          end

          to_remove.each do |path_string|
            path = Pathname.new('.').expand_path() / path_string
            path.rmtree if path.exist?
          end
        end
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Create Windows package.'
      end

      def self.details
        'Create Windows package.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :build_type,
                                       env_name: 'FL_CREATE_WINDOWS_PACKAGE_BUILD_TYPE',
                                       description: 'Build type',
                                       is_string: true,
                                       optional: true),
          FastlaneCore::ConfigItem.new(key: :path,
                                       env_name: 'FL_CREATE_WINDOWS_PACKAGE_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       optional: true)
        ]
      end

      def self.output
        [
          ['CREATE_WINDOWS_PACKAGE_OUTPUT_FILE', 'Created output file']
        ]
      end

      def self.authors
        ['@ntadej']
      end

      def self.is_supported?(platform)
        platform == :windows
      end
    end
  end
end
