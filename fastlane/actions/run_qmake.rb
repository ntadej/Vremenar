# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      RUN_QMAKE_PROJECT_PATH = :RUN_QMAKE_PROJECT_PATH
    end

    class RunQmakeAction < Action
      def self.run(params)
        build_number = params[:build_number] || Actions.lane_context[SharedValues::BUILD_NUMBER_VALUE]

        UI.message "Build path: #{params[:build_path]}"
        UI.message "Build number: #{build_number}"

        FileUtils.mkdir_p params[:build_path]
        relative_path = Pathname.new('.').relative_path_from(Pathname.new(params[:build_path])).to_s

        UI.message "Relative pro path: #{relative_path}/Vremenar.pro"

        Dir.chdir params[:build_path] do
          command = "qmake #{relative_path}/Vremenar.pro"
          command += ' -spec macx-ios-clang'
          command += ' CONFIG+=release CONFIG+=iphoneos CONFIG+=device CONFIG+=qtquickcompiler CONFIG+=store'
          command += " CUSTOM_BUILD=#{build_number}"

          Actions.sh command
        end

        Actions.lane_context[SharedValues::RUN_QMAKE_PROJECT_PATH] = "#{params[:build_path]}/Vremenar.xcodeproj"
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Run qmake to prepare the Xcode project'
      end

      def self.details
        'This action runs qmake with configured settings.' \
        ' Used to prepare the Xcode project for the standard build_app action.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :build_path,
                                       env_name: 'FL_RUN_QMAKE_BUILD_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       default_value: 'fastlane/build/ios/qmake'),
          FastlaneCore::ConfigItem.new(key: :build_number,
                                       env_name: 'FL_RUN_QMAKE_BUILD_NUMBER',
                                       description: 'Build number',
                                       is_string: false,
                                       optional: true)
        ]
      end

      def self.output
        [
          ['RUN_QMAKE_PROJECT_PATH', 'Created project path']
        ]
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
