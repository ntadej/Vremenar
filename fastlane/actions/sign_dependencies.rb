# frozen_string_literal: true

module Fastlane
  module Actions
    class SignDependenciesAction < Action
      def self.run(params)
        Actions.sh "codesign -f -s '#{params[:certificate_name]}' -o" \
                    " runtime './Carthage/Build/Countly.xcframework/macos-arm64_x86_64/Countly.framework'"
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Sign dependencies for Vremenar'
      end

      def self.details
        'This action signs dependencies for Vremenar.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :certificate_name,
                                       env_name: 'FL_SIGN_DEPENDENCIES_CERTIFICATE_NAME',
                                       description: 'Signing certificate name',
                                       is_string: true)
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
