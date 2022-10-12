# frozen_string_literal: true

# rubocop:disable Lint/MissingCopEnableDirective, Metrics/ClassLength, Metrics/CyclomaticComplexity, Metrics/PerceivedComplexity

module Fastlane
  module Actions
    module SharedValues
      RUN_CMAKE_PROJECT_PATH = :RUN_CMAKE_PROJECT_PATH
    end

    class RunCmakeAction < Action
      def self.run(params)
        UI.message "Platform/build type: #{params[:platform]}/#{params[:build_type]}"
        UI.message "Build number: #{params[:build_number]}"
        UI.message "Build path: #{params[:build_path]}"

        FileUtils.mkdir_p params[:build_path]
        relative_path = '.'

        pkg_certificate_name = get_pkg_certificate_name params

        command = "qt-cmake -S #{relative_path} -B #{params[:build_path]}"
        case params[:platform]
        when 'macos'
          command += " -G Ninja -DCMAKE_BUILD_TYPE='RelWithDebInfo'"
          command += " -DCMAKE_C_COMPILER_LAUNCHER='ccache' -DCMAKE_CXX_COMPILER_LAUNCHER='ccache'"
          command += " -DCMAKE_OSX_DEPLOYMENT_TARGET='10.14' -DCMAKE_OSX_ARCHITECTURES='x86_64;arm64'"
          command += " -DAPPLE_DEVELOPER_TEAM='#{params[:developer_team]}'" if params[:developer_team].empty?
          unless params[:certificate_name].empty?
            command += " -DAPPLE_CODE_SIGN_IDENTITY='#{params[:certificate_name]}'"
          end
          command += " -DAPPLE_PKG_SIGN_IDENTITY='#{pkg_certificate_name}'" unless pkg_certificate_name.empty?
          command += " -DAPPLE_PROVISIONING_PROFILE='#{params[:profile_name]}'" unless params[:profile_name].empty?
        when 'ios'
          command += ' -G Xcode'
          command += " -DCMAKE_OSX_DEPLOYMENT_TARGET='13.0' -DCMAKE_OSX_ARCHITECTURES='arm64'"
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
        end
        command += " -DAPPLE_XCODE_PATH='#{params[:xcode_path]}'" unless params[:xcode_path].empty?
        command += " -DVREMENAR_BUILD='#{params[:build_number]}'"
        command += ' -DVREMENAR_STORE=ON' if params[:build_type] == 'store'

        Actions.sh command

        Actions.lane_context[SharedValues::RUN_CMAKE_PROJECT_PATH] = if params[:platform] == 'ios'
                                                                       "#{params[:build_path]}/Vremenar.xcodeproj"
                                                                     else
                                                                       params[:build_path].to_s
                                                                     end
      end

      def self.get_pkg_certificate_name(params)
        if !params[:pkg_certificate_name].empty?
          params[:pkg_certificate_name]
        elsif params[:build_type] == 'store' && !params[:developer_team].empty?
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
                                       is_string: false),
          FastlaneCore::ConfigItem.new(key: :build_path,
                                       env_name: 'FL_RUN_CMAKE_BUILD_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       default_value: 'fastlane/build/macos/cmake'),
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
          ['RUN_CMAKE_PROJECT_PATH', 'Created project path']
        ]
      end

      def self.authors
        ['@ntadej']
      end

      def self.is_supported?(platform)
        platform == :mac
      end
    end
  end
end
