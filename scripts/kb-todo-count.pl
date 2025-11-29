#!/usr/bin/env perl
use strict;
use warnings;

# kb-todo-count.pl
#
# Count @todo annotations per layer/library so Pass 2 planning can focus on hotspots.
#
# Usage:
#   perl scripts/kb-todo-count.pl
#   perl scripts/kb-todo-count.pl layer-4/HiGHS layer-0/CoinUtils

use File::Find;

my @roots = @ARGV ? @ARGV : glob("layer-*");
my %counts;
my $total = 0;

find(
  {
    wanted => sub {
      return unless -f $_;
      return unless /\.(?:h|hpp|c|cpp)$/i;

      my $path = $File::Find::name;
      open my $fh, '<', $path or return;
      local $/;
      my $content = <$fh>;
      close $fh;

      my $todos = () = $content =~ /\@todo\b/gi;
      return unless $todos;

      $total += $todos;
      if ($path =~ m{^(layer-[^/]+)/([^/]+)}) {
        my $key = "$1/$2";
        $counts{$key} += $todos;
      }
      else {
        $counts{"(misc)"} += $todos;
      }
    },
    no_chdir => 1,
  },
  @roots
);

printf "Totals counted: %d\n", $total;
for my $key (sort keys %counts) {
  printf "%-25s %d\n", $key, $counts{$key};
}
