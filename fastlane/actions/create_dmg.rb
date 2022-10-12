# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      CREATE_DMG_OUTPUT_FILE = :CREATE_DMG_OUTPUT_FILE
    end

    class CreateDmgAction < Action
      def self.run(params)
        UI.message "Build path: #{params[:path]}"

        output_file = ''

        Dir.chdir params[:path] do
          Actions.sh './build_dmg.sh'

          dmg = false
          output_files = Pathname.glob '*.pkg'
          if output_files.empty?
            output_files = Pathname.glob '*.dmg'
            dmg = true
          end

          if dmg
            output_files[0].rename 'Vremenar.dmg'
            output_file = 'Vremenar.dmg'
          else
            output_files[0].rename 'Vremenar.pkg'
            output_file = 'Vremenar.pkg'
          end
        end

        UI.message "Output file: #{output_file}"

        Actions.lane_context[SharedValues::CREATE_DMG_OUTPUT_FILE] = "#{params[:path]}/#{output_file}"
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
          FastlaneCore::ConfigItem.new(key: :path,
                                       env_name: 'FL_CREATE_DMG_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       default_value: 'fastlane/build/macos/cmake')
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
