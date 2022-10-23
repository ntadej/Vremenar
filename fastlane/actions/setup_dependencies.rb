# frozen_string_literal: true

module Fastlane
  module Actions
    class SetupDependenciesAction < Action
      def self.run(params)
        UI.message "Setting up dependencies for: #{params[:platform]}"
        unless %w[ios macos].include? params[:platform]
          UI.error 'Unsupported platform'
          return
        end

        case params[:platform]
        when 'ios'
          Actions.sh './3rdparty/Firebase/iOS/download.sh'
          Actions.sh './3rdparty/Countly/iOS/download.sh'
        when 'macos'
          Actions.sh './3rdparty/Firebase/macOS/download.sh'
          Actions.sh './3rdparty/Countly/macOS/download.sh'
          unless params[:certificate_name].empty?
            Actions.sh "./3rdparty/Countly/macOS/sign.sh '#{params[:certificate_name]}'"
          end
          Actions.sh './3rdparty/Sparkle/macOS/download.sh'
          unless params[:certificate_name].empty?
            Actions.sh "./3rdparty/Sparkle/macOS/sign.sh '#{params[:certificate_name]}'"
          end
        end
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Setup dependencies for Vremenar'
      end

      def self.details
        'This action downloads and optionally signs dependencies for Vremenar.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :platform,
                                       env_name: 'FL_SETUP_DEPENDENCIES_PLATFORM',
                                       description: 'Platform',
                                       is_string: true,
                                       default_value: 'ios'),
          FastlaneCore::ConfigItem.new(key: :certificate_name,
                                       env_name: 'FL_SETUP_DEPENDENCIES_CERTIFICATE_NAME',
                                       description: 'Signing certificate name',
                                       is_string: true,
                                       default_value: '')
        ]
      end

      def self.output
        []
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
