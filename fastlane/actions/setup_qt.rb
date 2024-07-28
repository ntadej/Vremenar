# frozen_string_literal: true

module Fastlane
  module Actions
    class SetupQtAction < Action
      def self.run(params)
        UI.message "Setting up Qt for: #{params[:platform]}"
        unless %w[ios_qt6].include? params[:platform]
          UI.error 'Unsupported platform'
          return
        end

        qt_path = ENV['Qt6_Dir']

        UI.message "Qt path: #{qt_path}"

        # Remove unneeded stuff
        case params[:platform]
        when 'ios_qt6'
          to_remove = []
        end

        to_remove.each do |path_string|
          path = Pathname.new(qt_path) + path_string
          if path.exist?
            UI.message "Removing #{path}"
            path.rmtree
          end
        end
      end

      #####################################################
      # @!group Documentation
      #####################################################

      def self.description
        'Setup Qt for Vremenar'
      end

      def self.details
        'This action removes unneeded data from Qt installation for easier deployment.'
      end

      def self.available_options
        [
          FastlaneCore::ConfigItem.new(key: :platform,
                                       env_name: 'FL_SETUP_QT_PLATFORM',
                                       description: 'Platform',
                                       is_string: true,
                                       default_value: 'ios_qt6')
        ]
      end

      def self.output
        []
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
