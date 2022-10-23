# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      CREATE_ANDROID_PACKAGE_OUTPUT_FILE = :CREATE_ANDROID_PACKAGE_OUTPUT_FILE
    end

    class CreateAndroidPackageAction < Action
      def self.run(params)
        build_path = params[:path] || Actions.lane_context[SharedValues::RUN_CMAKE_PROJECT_PATH]
        build_type = params[:build_type] || Actions.lane_context[SharedValues::RUN_CMAKE_BUILD_TYPE]
        output_path = Actions.lane_context[SharedValues::RUN_CMAKE_OUTPUT_PATH] || build_path
        relative_output_path = Pathname.new(output_path).relative_path_from(Pathname.new(build_path))

        UI.message "Build path: #{build_path}"
        UI.message "Build type: #{build_type}"

        output_file_name = ''

        Dir.chdir build_path do
          case build_type
          when 'store/play'
            Actions.sh 'ninja aab'
            output_file_name = 'Vremenar.aab'
            FileUtils.mv 'src/android-build/build/outputs/bundle/release/android-build-release.aab',
                         "#{relative_output_path}/#{output_file_name}"
          else
            Actions.sh 'ninja apk'
            output_file_name = 'Vremenar.apk'
            FileUtils.mv 'src/android-build/Vremenar.apk', relative_output_path
          end
        end

        output_file = "#{output_path}/#{output_file_name}"
        UI.message "Output file: #{output_file}"

        Actions.lane_context[SharedValues::CREATE_ANDROID_PACKAGE_OUTPUT_FILE] = output_file
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Create APK/AAB'
      end

      def self.details
        'Create Android APK/AAB.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :build_type,
                                       env_name: 'FL_CREATE_ANDROID_PACKAGE_BUILD_TYPE',
                                       description: 'Build type',
                                       is_string: true,
                                       optional: true),
          FastlaneCore::ConfigItem.new(key: :path,
                                       env_name: 'FL_CREATE_ANDROID_PACKAGE_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       optional: true)
        ]
      end

      def self.output
        [
          ['CREATE_ANDROID_PACKAGE_OUTPUT_FILE', 'Created output file']
        ]
      end

      def self.authors
        ['@ntadej']
      end

      def self.is_supported?(platform)
        platform == :android
      end
    end
  end
end
