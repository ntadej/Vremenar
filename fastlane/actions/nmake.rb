# frozen_string_literal: true

module Fastlane
  module Actions
    class NmakeAction < Action
      def self.run(params)
        build_path = params[:path] || Actions.lane_context[SharedValues::RUN_QMAKE_PROJECT_PATH]

        UI.message "Build path: #{build_path}"

        Dir.chdir build_path do
          Actions.sh 'nmake'
        end
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Run nmake'
      end

      def self.details
        'This action runs nmake.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :path,
                                       env_name: 'FL_NMAKE_PATH',
                                       description: 'Build path',
                                       is_string: true,
                                       optional: true)
        ]
      end

      def self.output
        []
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
