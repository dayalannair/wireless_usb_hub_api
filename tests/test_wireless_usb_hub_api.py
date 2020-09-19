#!/usr/bin/env python

"""Tests for `wireless_usb_hub_api` package."""


import unittest
from click.testing import CliRunner

from wireless_usb_hub_api import wireless_usb_hub_api
from wireless_usb_hub_api import cli


class TestWireless_usb_hub_api(unittest.TestCase):
    """Tests for `wireless_usb_hub_api` package."""

    def setUp(self):
        """Set up test fixtures, if any."""

    def tearDown(self):
        """Tear down test fixtures, if any."""

    def test_000_something(self):
        """Test something."""

    def test_command_line_interface(self):
        """Test the CLI."""
        runner = CliRunner()
        result = runner.invoke(cli.main)
        assert result.exit_code == 0
        assert 'wireless_usb_hub_api.cli.main' in result.output
        help_result = runner.invoke(cli.main, ['--help'])
        assert help_result.exit_code == 0
        assert '--help  Show this message and exit.' in help_result.output
