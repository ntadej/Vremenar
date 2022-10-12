# frozen_string_literal: true

module Fastlane
  module Actions
    class NinjaAction < Action
      def self.run(params)
        UI.message "Build path: #{params[:path]}"

        Dir.chdir params[:path] do
          Actions.sh 'ninja'
        end
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Run ninja'
      end

      def self.details
        'This action runs ninja.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :path,
                                       env_name: 'FL_NINJA_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       default_value: 'fastlane/build/macos/cmake')
        ]
      end

      def self.output
        []
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
