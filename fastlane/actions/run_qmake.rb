# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      RUN_QMAKE_BUILD_TYPE = :RUN_QMAKE_BUILD_TYPE
      RUN_QMAKE_OUTPUT_PATH = :RUN_QMAKE_OUTPUT_PATH
      RUN_QMAKE_PLATFORM = :RUN_QMAKE_PLATFORM
      RUN_QMAKE_PROJECT_PATH = :RUN_QMAKE_PROJECT_PATH
    end

    class RunQmakeAction < Action
      def self.run(params)
        build_number = params[:build_number] || Actions.lane_context[SharedValues::BUILD_NUMBER_VALUE]

        UI.message "Platform/build type: #{params[:platform]}/#{params[:build_type]}"
        UI.message "Build number: #{build_number}"
        UI.message "Build path: #{params[:build_path]}"
        UI.message "Output path: #{params[:output_path]}"

        FileUtils.mkdir_p params[:build_path]
        FileUtils.mkdir_p params[:output_path]
        relative_path = Pathname.new('.').relative_path_from(Pathname.new(params[:build_path])).to_s

        UI.message "Relative pro path: #{relative_path}/Vremenar.pro"

        command = "qmake #{relative_path}/Vremenar.pro"
        case params[:platform]
        when 'ios'
          command += ' -spec macx-ios-clang'
          command += ' CONFIG+=release CONFIG+=iphoneos CONFIG+=device CONFIG+=qtquickcompiler CONFIG+=store'
        when 'windows'
          command += ' -spec win32-msvc'
          command += ' CONFIG+=release CONFIG+=qtquickcompiler CONFIG+=store'
          command += " WINDOWS_NAME='#{params[:windows_name]}'" unless params[:windows_name].empty?
          command += " WINDOWS_PUBLISHER='#{params[:windows_publisher]}'" unless params[:windows_publisher].empty?
        end
        command += " CUSTOM_BUILD=#{build_number}"

        Dir.chdir params[:build_path] do
          Actions.sh command
        end

        Actions.lane_context[SharedValues::RUN_QMAKE_BUILD_TYPE] = params[:build_type].to_s
        Actions.lane_context[SharedValues::RUN_QMAKE_OUTPUT_PATH] = params[:output_path].to_s
        Actions.lane_context[SharedValues::RUN_QMAKE_PLATFORM] = params[:platform].to_s
        Actions.lane_context[SharedValues::RUN_QMAKE_PROJECT_PATH] = if params[:platform] == 'ios'
                                                                       "#{params[:build_path]}/Vremenar.xcodeproj"
                                                                     else
                                                                       params[:build_path].to_s
                                                                     end
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Run qmake to prepare the build'
      end

      def self.details
        'This action runs qmake with configured settings.' \
        ' Used to prepare the Xcode project for the standard build_app action.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :platform,
                                       env_name: 'FL_RUN_QMAKE_PLATFORM',
                                       description: 'Platform',
                                       is_string: true),
          FastlaneCore::ConfigItem.new(key: :build_type,
                                       env_name: 'FL_RUN_QMAKE_BUILD_TYPE',
                                       description: 'Build type',
                                       is_string: true),
          FastlaneCore::ConfigItem.new(key: :build_number,
                                       env_name: 'FL_RUN_QMAKE_BUILD_NUMBER',
                                       description: 'Build number',
                                       is_string: false,
                                       optional: true),
          FastlaneCore::ConfigItem.new(key: :build_path,
                                       env_name: 'FL_RUN_QMAKE_BUILD_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       default_value: 'fastlane/build/ios/qmake'),
          FastlaneCore::ConfigItem.new(key: :output_path,
                                       env_name: 'FL_RUN_QMAKE_OUTPUT_PATH',
                                       description: 'Output path',
                                       is_string: true,
                                       default_value: 'fastlane/build/ios'),
          FastlaneCore::ConfigItem.new(key: :windows_name,
                                       env_name: 'FL_RUN_QMAKE_WINDOWS_NAME',
                                       description: 'Windows name',
                                       is_string: true,
                                       default_value: 'Vremenar'),
          FastlaneCore::ConfigItem.new(key: :windows_publisher,
                                       env_name: 'FL_RUN_QMAKE_WINDOWS_PUBLISHER',
                                       description: 'Windows publisher',
                                       is_string: true,
                                       default_value: 'CN=TadejNovak')
        ]
      end

      def self.output
        [
          ['RUN_QMAKE_BUILD_TYPE', 'Project build type'],
          ['RUN_QMAKE_OUTPUT_PATH', 'Project output path'],
          ['RUN_QMAKE_PLATFORM', 'Platform the project is built for'],
          ['RUN_QMAKE_PROJECT_PATH', 'Created project path']
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
