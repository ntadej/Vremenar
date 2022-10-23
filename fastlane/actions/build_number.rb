# frozen_string_literal: true

module Fastlane
  module Actions
    module SharedValues
      BUILD_NUMBER_VALUE = :BUILD_NUMBER_VALUE
    end

    class BuildNumberAction < Action
      def self.run(params)
        UI.message "Offset: #{params[:offset]}"

        revision = Actions.sh 'git rev-list --count HEAD', log: false
        build_number = revision.to_i + params[:offset]

        UI.message "Build number: #{build_number}"

        Actions.lane_context[SharedValues::BUILD_NUMBER_VALUE] = build_number
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Get build number'
      end

      def self.details
        'This action gets build number from git revisions with given offset.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :offset,
                                       env_name: 'FL_BUILD_NUMBER_OFFSET',
                                       description: 'Build number offset',
                                       is_string: false,
                                       default_value: 0)
        ]
      end

      def self.output
        [
          ['BUILD_NUMBER_VALUE', 'Generated build number']
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
