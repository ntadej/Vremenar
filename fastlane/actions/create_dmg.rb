# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      CREATE_DMG_OUTPUT_FILE = :CREATE_DMG_OUTPUT_FILE
    end

    class CreateDmgAction < Action
      def self.run(params)
        build_path = params[:path] || Actions.lane_context[SharedValues::RUN_CMAKE_PROJECT_PATH]
        build_type = params[:build_type] || Actions.lane_context[SharedValues::RUN_CMAKE_BUILD_TYPE]
        output_path = Actions.lane_context[SharedValues::RUN_CMAKE_OUTPUT_PATH] || build_path
        relative_output_path = Pathname.new(output_path).relative_path_from(Pathname.new(build_path))

        UI.message "Build path: #{build_path}"
        UI.message "Build type: #{build_type}"

        output_file_name = ''

        Dir.chdir build_path do
          Actions.sh './build_dmg.sh'

          if build_type == 'store'
            output_files = Pathname.glob '*.pkg'
            output_files[0].rename 'Vremenar.pkg'
            output_file_name = 'Vremenar.pkg'
          else
            output_files = Pathname.glob '*.dmg'
            output_files[0].rename 'Vremenar.dmg'
            output_file_name = 'Vremenar.dmg'
          end

          FileUtils.mv output_file_name, relative_output_path
        end

        output_file = "#{output_path}/#{output_file_name}"

        UI.message "Output file: #{output_file}"

        Actions.lane_context[SharedValues::CREATE_DMG_OUTPUT_FILE] = output_file
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Create DMG'
      end

      def self.details
        'Create DMG using generated script.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :build_type,
                                       env_name: 'FL_CREATE_DMG_BUILD_TYPE',
                                       description: 'Build type',
                                       is_string: true,
                                       optional: true),
          FastlaneCore::ConfigItem.new(key: :path,
                                       env_name: 'FL_CREATE_DMG_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       optional: true)
        ]
      end

      def self.output
        [
          ['CREATE_DMG_OUTPUT_FILE', 'Created output file']
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
