# frozen_string_literal: true

# rubocop:disable Lint/MissingCopEnableDirective, Metrics/ClassLength, Metrics/CyclomaticComplexity, Metrics/PerceivedComplexity

module Fastlane
  module Actions
    module SharedValues
      RUN_CMAKE_BUILD_TYPE = :RUN_CMAKE_BUILD_TYPE
      RUN_CMAKE_OUTPUT_PATH = :RUN_CMAKE_OUTPUT_PATH
      RUN_CMAKE_PLATFORM = :RUN_CMAKE_PLATFORM
      RUN_CMAKE_PROJECT_PATH = :RUN_CMAKE_PROJECT_PATH
    end

    class RunCmakeAction < Action
      def self.run(params)
        build_number = params[:build_number] || Actions.lane_context[SharedValues::BUILD_NUMBER_VALUE]

        UI.message "Platform/build type: #{params[:platform]}/#{params[:build_type]}"
        UI.message "Build number: #{build_number}"
        UI.message "Build path: #{params[:build_path]}"
        UI.message "Output path: #{params[:output_path]}"

        FileUtils.mkdir_p params[:build_path]
        FileUtils.mkdir_p params[:output_path]
        relative_path = '.'

        command = "qt-cmake -S #{relative_path} -B #{params[:build_path]}"
        case params[:platform]
        when 'macos'
          pkg_certificate_name = get_pkg_certificate_name params
          if params[:build_type] == 'store'
            command += ' -G Xcode'
            unless params[:certificate_name].empty?
              command += " -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY='#{params[:certificate_name]}'"
            end
            command += " -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGN_STYLE='Manual'"
            unless params[:developer_team].empty?
              command += " -DCMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM='#{params[:developer_team]}'"
            end
            unless params[:profile_name].empty?
              command += " -DCMAKE_XCODE_ATTRIBUTE_PROVISIONING_PROFILE_SPECIFIER='#{params[:profile_name]}'"
            end
          else
            command += ' -G Ninja'
            command += " -DCMAKE_BUILD_TYPE='RelWithDebInfo'"
            command += " -DAPPLE_PROVISIONING_PROFILE='#{params[:profile_name]}'" unless params[:profile_name].empty?
          end
          command += " -DCMAKE_C_COMPILER_LAUNCHER='ccache' -DCMAKE_CXX_COMPILER_LAUNCHER='ccache'"
          command += " -DCMAKE_OSX_DEPLOYMENT_TARGET='11.0' -DCMAKE_OSX_ARCHITECTURES='x86_64;arm64'"
          command += " -DAPPLE_DEVELOPER_TEAM='#{params[:developer_team]}'" unless params[:developer_team].empty?
          unless params[:certificate_name].empty?
            command += " -DAPPLE_CODE_SIGN_IDENTITY='#{params[:certificate_name]}'"
          end
          command += " -DAPPLE_PKG_SIGN_IDENTITY='#{pkg_certificate_name}'" unless pkg_certificate_name.empty?
          if Actions.lane_context[SharedValues::XCODE_METADATA_XCODE_VERSION_CODE]
            command += ' -DAPPLE_XCODE_VERSION_CODE='
            command += "'#{Actions.lane_context[SharedValues::XCODE_METADATA_XCODE_VERSION_CODE]}'"
          end
          if Actions.lane_context[SharedValues::XCODE_METADATA_XCODE_BUILD]
            command += " -DAPPLE_XCODE_BUILD='#{Actions.lane_context[SharedValues::XCODE_METADATA_XCODE_BUILD]}'"
          end
          if Actions.lane_context[SharedValues::XCODE_METADATA_SDK_VERSION]
            command += " -DAPPLE_SDK_VERSION='#{Actions.lane_context[SharedValues::XCODE_METADATA_SDK_VERSION]}'"
          end
          if Actions.lane_context[SharedValues::XCODE_METADATA_SDK_BUILD]
            command += " -DAPPLE_SDK_BUILD='#{Actions.lane_context[SharedValues::XCODE_METADATA_SDK_BUILD]}'"
          end
          if Actions.lane_context[SharedValues::XCODE_METADATA_SDK_PLATFORM_VERSION]
            command += ' -DAPPLE_SDK_PLATFORM_VERSION='
            command += "'#{Actions.lane_context[SharedValues::XCODE_METADATA_SDK_PLATFORM_VERSION]}'"
          end
          if Actions.lane_context[SharedValues::XCODE_METADATA_OS_BUILD]
            command += ' -DAPPLE_BUILD_MACHINE_OS_BUILD='
            command += "'#{Actions.lane_context[SharedValues::XCODE_METADATA_OS_BUILD]}'"
          end
        when 'ios'
          command += ' -G Xcode'
          command += " -DCMAKE_OSX_DEPLOYMENT_TARGET='14.0' -DCMAKE_OSX_ARCHITECTURES='arm64'"
          command += " -DQMapLibre_DIR=\"#{ENV['QMapLibre_DIR']}/lib/cmake/QMapLibre\""
          unless params[:certificate_name].empty?
            command += " -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY='#{params[:certificate_name]}'"
          end
          command += " -DCMAKE_XCODE_ATTRIBUTE_CODE_SIGN_STYLE='Manual'"
          unless params[:developer_team].empty?
            command += " -DCMAKE_XCODE_ATTRIBUTE_DEVELOPMENT_TEAM='#{params[:developer_team]}'"
          end
          unless params[:profile_name].empty?
            command += " -DCMAKE_XCODE_ATTRIBUTE_PROVISIONING_PROFILE_SPECIFIER='#{params[:profile_name]}'"
          end
        when 'android'
          command += " -G Ninja -DCMAKE_BUILD_TYPE='RelWithDebInfo'"
          command += " -DCMAKE_C_COMPILER_LAUNCHER='ccache' -DCMAKE_CXX_COMPILER_LAUNCHER='ccache'"
          case params[:build_type]
          when 'store/play'
            command += " -DQT_ANDROID_ABIS='armeabi-v7a;arm64-v8a;x86_64;x86'"
          when 'store/firetv'
            command += " -DQT_ANDROID_ABIS='armeabi-v7a'"
            command += ' -DVREMENAR_POSITIONING=OFF'
          when 'store/fire32'
            command += " -DQT_ANDROID_ABIS='armeabi-v7a'"
          when 'store/fire64'
            command += " -DQT_ANDROID_ABIS='arm64-v8a'"
          when 'store/amazon'
            command += " -DQT_ANDROID_ABIS='armeabi-v7a;arm64-v8a;x86_64;x86'"
          else
            command += " -DQT_ANDROID_ABIS='armeabi-v7a;arm64-v8a;x86_64;x86'"
          end
        when 'linux'
          command += " -G Ninja -DCMAKE_BUILD_TYPE='Release'"
          command += " -DCMAKE_C_COMPILER_LAUNCHER='ccache' -DCMAKE_CXX_COMPILER_LAUNCHER='ccache'"
          command += " -DCMAKE_INSTALL_PREFIX='/usr'"
        end
        command += " -DAPPLE_XCODE_PATH='#{params[:xcode_path]}'" unless params[:xcode_path].empty?
        command += " -DVREMENAR_BUILD='#{build_number}'"
        command += ' -DVREMENAR_STORE=ON' if params[:build_type].include? 'store'

        Actions.sh command

        Actions.lane_context[SharedValues::RUN_CMAKE_BUILD_TYPE] = params[:build_type].to_s
        Actions.lane_context[SharedValues::RUN_CMAKE_OUTPUT_PATH] = params[:output_path].to_s
        Actions.lane_context[SharedValues::RUN_CMAKE_PLATFORM] = params[:platform].to_s
        Actions.lane_context[SharedValues::RUN_CMAKE_PROJECT_PATH] = if params[:platform] == 'ios'
                                                                       "#{params[:build_path]}/Vremenar.xcodeproj"
                                                                     elsif params[:build_type] == 'store'
                                                                       "#{params[:build_path]}/Vremenar.xcodeproj"
                                                                     else
                                                                       params[:build_path].to_s
                                                                     end
      end

      def self.get_pkg_certificate_name(params)
        if !params[:pkg_certificate_name].empty?
          params[:pkg_certificate_name]
        elsif (params[:build_type].include? 'store') && !params[:developer_team].empty?
          "3rd Party Mac Developer Installer: Tadej Novak (#{params[:developer_team]})"
        else
          ''
        end
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Run cmake to prepare the project for building'
      end

      def self.details
        'This action runs qt-cmake with configured settings.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :platform,
                                       env_name: 'FL_RUN_CMAKE_PLATFORM',
                                       description: 'Platform',
                                       is_string: true),
          FastlaneCore::ConfigItem.new(key: :build_type,
                                       env_name: 'FL_RUN_CMAKE_BUILD_TYPE',
                                       description: 'Build type',
                                       is_string: true),
          FastlaneCore::ConfigItem.new(key: :build_number,
                                       env_name: 'FL_RUN_CMAKE_BUILD_NUMBER',
                                       description: 'Build number',
                                       is_string: false,
                                       optional: true),
          FastlaneCore::ConfigItem.new(key: :build_path,
                                       env_name: 'FL_RUN_CMAKE_BUILD_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       default_value: 'fastlane/build/macos/cmake'),
          FastlaneCore::ConfigItem.new(key: :output_path,
                                       env_name: 'FL_RUN_CMAKE_OUTPUT_PATH',
                                       description: 'Output path',
                                       is_string: true,
                                       default_value: 'fastlane/build/macos'),
          FastlaneCore::ConfigItem.new(key: :developer_team,
                                       env_name: 'FL_RUN_CMAKE_DEVELOPER_TEAM',
                                       description: 'Developer team',
                                       is_string: true,
                                       default_value: ''),
          FastlaneCore::ConfigItem.new(key: :certificate_name,
                                       env_name: 'FL_RUN_CMAKE_CERTIFICATE_NAME',
                                       description: 'Signing certificate name',
                                       is_string: true,
                                       default_value: ''),
          FastlaneCore::ConfigItem.new(key: :pkg_certificate_name,
                                       env_name: 'FL_RUN_CMAKE_PKG_CERTIFICATE_NAME',
                                       description: 'Packaging certificate name',
                                       is_string: true,
                                       default_value: ''),
          FastlaneCore::ConfigItem.new(key: :profile_name,
                                       env_name: 'FL_RUN_CMAKE_PROFILE_NAME',
                                       description: 'Provisioning profile name',
                                       is_string: true,
                                       default_value: ''),
          FastlaneCore::ConfigItem.new(key: :xcode_path,
                                       env_name: 'FL_RUN_CMAKE_XCODE_PATH',
                                       description: 'Xcode path',
                                       is_string: true,
                                       default_value: '')
        ]
      end

      def self.output
        [
          ['RUN_CMAKE_BUILD_TYPE', 'Project build type'],
          ['RUN_CMAKE_OUTPUT_PATH', 'Project output path'],
          ['RUN_CMAKE_PLATFORM', 'Platform the project is built for'],
          ['RUN_CMAKE_PROJECT_PATH', 'Created project path']
        ]
      end

      def self.authors
        ['@ntadej']
      end

      def self.is_supported?(_platform)
        true
      end
    end
  end
end
